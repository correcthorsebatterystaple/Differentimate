#if !defined(NODE)
#define NODE

#include <string>
#include <iostream>
enum Type {OPERATOR, NUMBER, UNKNOWN};

class Node {
  private:
    std::string value;
    Type type;
    Node* right;
    Node* left;
    bool isNumber(std::string str) {
      for (int i = 0; i < str.length(); i++) {
        if (!std::isdigit(str[i])) return false;
      }
      return true;
    }
    bool isOperator(std::string str) {
      return str == "+" || str == "-" || str == "*" || str == "/" || str == "^";
    }
  public:
    Node(std::string value) {
      this->value = value;
      this->right = NULL;
      this->left = NULL;
      if (isOperator(value)) this->type = OPERATOR;
      else if (isNumber(value)) this->type = NUMBER;
      else this->type = UNKNOWN;
    }
    Node* setRight(Node* right) {
      this->right = right;
      return this->right;
    }
    Node* setLeft(Node* left) {
      this->left = left;
      return this->left;
    }
    std::string getValue() {
      return value;
    }
    Node* getLeft() {
      return this->left;
    }
    Node* getRight() {
      return this->right;
    }
    Type getType() {
      return this->type;
    }
    bool find(std::string value) {
      if (this->value == value) return true;
      else if (!this->right) return false;
      else {
        return this->left->find(value) || this->right->find(value);
      }
    }
    void print(std::string spaces) {
      std::cout << spaces << this->value ;
      if (this->type == NUMBER) std::cout << " NUMBER" << std::endl;
      else if (this->type == OPERATOR) std::cout << " OPERATOR" << std::endl;
      else if (this->type == UNKNOWN) std::cout << " UNKNOWN" << std::endl;
      else std::cout << " ERROR" << std::endl;
      spaces = spaces + "| ";
      if (this->right && this->left){
        this->left->print(spaces);
        this->right->print(spaces);
      }
    }

    std::string getString() {
      std::string str = "";
      if (this->left) {
        str += "(";
        str += this->left->getString();
      }
      str += this->value;
      if (this->right) {
        str += this->right->getString();
        str += ")";
      }
      return str;
    }

    std::string differentiate(std::string wrt) {
    if (this->type == NUMBER) {
      return "0";
    } else if (this->type == UNKNOWN) {
      if (this->value == wrt) return "1";
      else return "0";
    } else if (this->type == OPERATOR) {
      if (!this->find(wrt)) return "0";
      std::string op = this->value;
      if (op == "+" || op == "-") {
        std::string left = this->left->differentiate(wrt);
        std::string right = this->right->differentiate(wrt);
        return left + op + right;
      } else if (op == "*") {
        // product rule
        return "(" + this->left->getString() + ")" + "*" + "(" + this->right->differentiate(wrt) + ")" + "+"  + "(" + this->left->differentiate(wrt) + ")" + "*" + "(" + this->right->getString() + ")";

      } else if (op == "/") {
        std::string top = this->left->getString();
        std::string bottom = this->right->getString();
        std::string dTop = this->left->differentiate(wrt);
        std::string dBottom = this->right->differentiate(wrt);

        return "(" + dTop + "*" + bottom + "-" + top + "*" + dBottom + ")/" + "(" + bottom + ")^2";

      } else if (op == "^") {
        //TODO : differentiation for exponents
        return "0";
      }
    }
    return "Error";
  }
};

#endif // NODE
