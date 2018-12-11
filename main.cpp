#include <iostream>
#include <string>
#include <stack>
#include <typeinfo>
#include <queue>
using namespace std;

bool isOperator(char x) {
  return x == '+' || x == '-';
}

int operate(int left, int right, char op) {
  if (op == '+') {
    return left + right;
  } else if (op == '-') {
    return left - right;
  }
}

int precedence(char op) {
  if (op == '^') return 3;
  if (op == '*' || op == '/') return 2;
  if (op == '+' || op == '-') return 1;
  return 0;
}

int main(int argc, char const *argv[])
{
  string exp;
  exp = argv[1];
  stack<char> operators;
int comparePrecedence(char op1, char op2) {
  return precedence(op1) - precedence(op2);
}

bool isLeftAssoc(char op) {
  return op == '/' || op == '-';
}

  queue<char> postfix;
  stack<char> calc;


  for(int i = 0; i < exp.length(); i++) {
    if (!isOperator(exp[i])) {
      postfix.push(exp[i]-48);
    } else {
      operators.push(exp[i]);
    }
  }

  while (!operators.empty()) {
    postfix.push(operators.top());
    operators.pop();
  }

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
