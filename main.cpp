#include <iostream>
#include <string>
#include <stack>
#include <typeinfo>
#include <queue>
#include <cmath>
using namespace std;

bool isOperator(char x) {
  return x == '+' || x == '-' || x == '*' || x == '/' || x == '^';
}

int operate(int left, int right, char op) {
  switch (op) {
    case '+' : return left + right;
    case '-' : return left - right;
    case '*' : return left * right;
    case '/' : return left / right;
    case '^' : return pow(left,right);
    default : return 0;
  }
}

int precedence(char op) {
  if (op == '^') return 3;
  if (op == '*' || op == '/') return 2;
  if (op == '+' || op == '-') return 1;
  return 0;
}

int comparePrecedence(char op1, char op2) {
  return precedence(op1) - precedence(op2);
}

bool isLeftAssoc(char op) {
  return op == '/' || op == '-';
}

int main(int argc, char const *argv[])
{
  string exp;
  exp = argv[1];
  stack<char> operators;
  queue<char> postfix;
  stack<char> calc;

  //TODO: make work for multiple digit values by tokenizing input

  // iterate through argument string (expression)
  for(int i = 0; i < exp.length(); i++) {
    char token = exp[i];
    if (token >= '0' && token <= '9'){ // if token is number
      postfix.push(token-'0');
    } else if (isOperator(token)) { // if token is operator
      // while operators are not empty and, 
      // token has lower precedence than top or
      // token has same precedence as top and is left associative 
      while (!operators.empty() && (
        comparePrecedence(operators.top(),token) > 0 || (
          comparePrecedence(operators.top(),token)==0 && 
          isLeftAssoc(operators.top())
          )
        )
      ) {
        postfix.push(operators.top());
        operators.pop();
      }
      operators.push(token);
    }
  }

  // push all remaining operators to the output
  while (!operators.empty()) {
    postfix.push(operators.top());
    operators.pop();
  }

  // read from output
  while (!postfix.empty()) {
    if (!isOperator(postfix.front())) {
      calc.push(postfix.front());
    } else {
      int right = calc.top();
      calc.pop();
      int left = calc.top();
      calc.pop();
      printf("%d %c %d = %d\n", left, postfix.front(), right, operate(left, right, postfix.front()));
      
      calc.push(operate(left, right, postfix.front()));
    }
    postfix.pop();
  }

  printf("%d", calc.top());
  cout << endl;
  return 0;
}
