#include <iostream>
#include <string>
#include <stack>
#include <typeinfo>
#include <queue>
#include <cmath>
#include "node.h"
using namespace std;

// returns the precedence of the operator
int precedence(string op) {
  if (op == "^") return 5;
  if (op == "/") return 4;
  if (op == "*") return 3;
  if (op == "+") return 2;
  if (op == "-") return 1;
  return 0;
}

// compares the precedences of param operators
int compare(string op1, string op2) {
  return precedence(op1) - precedence(op2);
}

// checks if operator is left associative
bool isLeftAssoc(string op) {
  return op == "/" || op == "-";
}

// checks if character is an operator
bool isOperator(string x) {
  return x == "+" || x == "-" || x == "*" || x == "/" || x == "^";
}

// tokenizes given string
vector<string> tokenize(string exp) {
  vector<string> tokens;
  // iterate through the expression and tokenize
  for (int i = 0; i < exp.length(); i++) {
    string token(1,exp[i]);
    // if it is a variable being implicitly multiplied
    if (i-1 >= 0 && !isOperator(string(1,exp[i-1])) && isalpha(exp[i]) && exp[i-1] != '(') tokens.push_back("*");
    if (i-1 >= 0 && !isOperator(string(1,exp[i-1])) && 
    exp[i-1] != '(' && exp[i] == '(') tokens.push_back("*");
    //TODO: tokenize functions
    // make multidigit numbers one token
    while (i+1 < exp.length() && isdigit(exp[i]) &&isdigit(exp[i+1])) {
      token += exp[i+1];
      i++;
    }
    tokens.push_back(token);
  }
  return tokens;
}

// converts an infix tokenized vector to a postfix tokenized vector
vector<string> infixToPostfix(vector<string> tokens) {

  stack<string> operators;
  vector<string> postfix;

  for(int i = 0; i < tokens.size(); i++) {
    string token = tokens.at(i);
    if (isOperator(token)) { // if token is operator
      // while operators are not empty and, 
      // token has lower precedence than top or
      // token has same precedence as top and is left associative 
      while (!operators.empty() && (
        compare(operators.top(),token) > 0 || (
          compare(operators.top(),token)==0 && 
          isLeftAssoc(operators.top())
          ) && operators.top() != "(" 
        )
      ) {
        postfix.push_back(operators.top());
        operators.pop();
      }
      operators.push(token);
    } else if (token == "(") {
      operators.push(token);
    } else if (token == ")") { 
      while (operators.top() != "(") {
        postfix.push_back(operators.top());
        operators.pop();
      }
      operators.pop();
    } else {
      postfix.push_back(token);
    }
  }
  // push all remaining operators to the output
  while (!operators.empty()) {
    postfix.push_back(operators.top());
    operators.pop();
  }
  
  return postfix;
}

// converts given vector to a queue
queue<string> vectorToQueue(vector<string> v) {
  queue<string> q;
  for (size_t i = 0; i < v.size(); i++) {
    q.push(v.at(i));
  }
  return q;
}

// parses the given postfix tokens into a parse tree
Node* parseTree(vector<string> tokens) {
  queue<string> postfix = vectorToQueue(tokens);
  stack<Node*> operators;
  stack<Node*> nodes;
  while (!postfix.empty()) {
    string token = postfix.front();
    if (isOperator(token)) {
      Node* op = new Node(token);
      op->setRight(nodes.top());
      nodes.pop();
      op->setLeft(nodes.top());
      nodes.pop();
      nodes.push(op);
    } else {
      Node* num = new Node(token);
      nodes.push(num);
    }
    postfix.pop();
  }
  return nodes.top();
}

int main(int argc, char const *argv[])
{
  string exp;
  exp = argv[1];

  vector<string> tokens = tokenize(exp);
  // print all the tokens
  for (int i = 0; i < tokens.size()-1; i++) {
    cout << tokens.at(i) << ",";
  }
  cout << tokens.at(tokens.size()-1) << endl;
  tokens = infixToPostfix(tokens);

  Node* root = parseTree(tokens);
  // string spaces = "";
  // root->print(spaces);

  cout << root->differentiate("x") << endl;
  
  return 0;
}
