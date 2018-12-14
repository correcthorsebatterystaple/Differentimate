#include <iostream>
#include <string>
#include <stack>
#include <typeinfo>
#include <queue>
#include <cmath>
using namespace std;

bool isOperator(string x) {
  return x == "+" || x == "-" || x == "*" || x == "/" || x == "^";
}

int operate(int left, int right, string op) {
  if (op == "+") return left + right;
  if (op == "-") return left - right;
  if (op == "*") return left * right;
  if (op == "/") return left / right;
  if (op == "^") return pow(left,right);
  return 0;
}

int precedence(string op) {
  if (op == "^") return 3;
  if (op == "*" || op == "/") return 2;
  if (op == "+" || op == "-") return 1;
  return 0;
}

int comparePrecedence(string op1, string op2) {
  return precedence(op1) - precedence(op2);
}

bool isLeftAssoc(string op) {
  return op == "/" || op == "-";
}

bool isDigit(string s) {
  for (int i = 0; i < s.length(); i++) {
    if (!isdigit(s[i])) return false;
  }
  return true;
}

int main(int argc, char const *argv[])
{
  string exp;
  exp = argv[1];
  stack<string> operators;
  queue<string> postfix;
  stack<string> calc;

  vector<string> tokens;

  for (int i = 0; i < exp.length(); i++) {
    string token(1,exp[i]);
    if (i-1 >= 0 && !isOperator(string(1,exp[i-1])) && isalpha(exp[i])) tokens.push_back("*");
    while (i+1 < exp.length() && isdigit(exp[i]) &&isdigit(exp[i+1])) {
      token += exp[i+1];
      i++;
    }
    tokens.push_back(token);
  }

  // iterate through argument string (expression)
  for(int i = 0; i < tokens.size(); i++) {
    string token = tokens.at(i);
    //// cout << "token: " << token << endl;
    if (isOperator(token)) { // if token is operator
      //// cout << "  token is an operator" << endl;
      // while operators are not empty and, 
      // token has lower precedence than top or
      // token has same precedence as top and is left associative 
      while (!operators.empty() && (
        comparePrecedence(operators.top(),token) > 0 || (
          comparePrecedence(operators.top(),token)==0 && 
          isLeftAssoc(token)
          )
        )
      ) {
        //// cout << "    popping out " << operators.top() << endl;
        postfix.push(operators.top());
        operators.pop();
      }
      //// cout << "  pushing " << token << endl;
      operators.push(token);
    } else {
      postfix.push(token);
    }
  }

  // push all remaining operators to the output
  while (!operators.empty()) {
    postfix.push(operators.top());
    operators.pop();
  }
  // print out the postfix queue
  while (!postfix.empty()) {
    cout << postfix.front() << " ";
    postfix.pop();
  }
  cout << endl;

  // // read from output
  // while (!postfix.empty()) {
  //   if (!isOperator(postfix.front())) {
  //     calc.push(stoi(postfix.front());
  //   } else {
  //     int right = calc.top();
  //     calc.pop();
  //     int left = calc.top();
  //     calc.pop();
  //     printf("%d %c %d = %d\n", left, postfix.front().c_str(), right, operate(left, right, postfix.front()));
      
  //     calc.push(operate(left, right, postfix.front()));
  //   }
  //   postfix.pop();
  // }

  // printf("%d", calc.top());
  // cout << endl;
  // return 0;
}
