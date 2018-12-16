#if !defined(NODE)
#define NODE

#include <string>
#include <iostream>
class Node {
  private:
    std::string value;
    Node* right;
    Node* left;
  public:
    Node(std::string value) {
      this->value = value;
      this->right = NULL;
      this->left = NULL;
    }
    Node(std::string value, Node* left, Node* right) {
      this->value = value;
      this->right = right;
      this->left = left;
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
};

#endif // NODE
