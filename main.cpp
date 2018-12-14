#include <iostream>
#include <string>
#include <stack>
#include <typeinfo>
#include <queue>
#include <cmath>
#include "DiffUnit.h"
using namespace std;

bool isOperator(string x) {
  return x == "+" || x == "-" || x == "*" || x == "/" || x == "^";
}

bool isNumber(string s) {
  for (int i = 0; i < s.length(); i++) {
    if (!isdigit(s[i])) return false;
  }
  return true;
}

vector<string> smushBrackets(vector<string> tokens) {
  vector<string> newTokens;
  int brackets = 0;
  string token = "";
  for (int i = 0; i < tokens.size(); i++) {
    if (tokens.at(i) == "(") {
      // checks if already in brackets or not
      if (!brackets) newTokens.push_back(tokens.at(i));
      else token += tokens.at(i);
      brackets++;
      continue;
    }
    if (tokens.at(i) == ")") {
      brackets--;
      // checks if now in brackets or not
      if (!brackets) {
        newTokens.push_back(token);
        newTokens.push_back(tokens.at(i));
        token = "";
      } else token += tokens.at(i);
      continue;
    }
    if (brackets) token += tokens.at(i);
    else newTokens.push_back(tokens.at(i));
  }
  return newTokens;
}

vector<string> tokenize(string exp) {
  vector<string> tokens;
  // iterate through the expression and tokenize
  for (int i = 0; i < exp.length(); i++) {
    string token(1,exp[i]);
    // if it is a variable being implicitly multiplied
    if (i-1 >= 0 && !isOperator(string(1,exp[i-1])) && isalpha(exp[i])) tokens.push_back("*");
    if (i-1 >= 0 && !isOperator(string(1,exp[i-1])) && 
    exp[i-1] != '(' && exp[i] == '(') tokens.push_back("*");
    // make multidigit numbers one token
    while (i+1 < exp.length() && isdigit(exp[i]) &&isdigit(exp[i+1])) {
      token += exp[i+1];
      i++;
    }
    tokens.push_back(token);
  }
  return tokens;
}

int main(int argc, char const *argv[])
{
  string exp;
  exp = argv[1];
  stack<string> operators;
  queue<string> postfix;
  stack<string> calc;

  vector<string> tokens = smushBrackets(tokenize(exp));

  // print all the tokens
  for (int i = 0; i < tokens.size()-1; i++) {
    cout << tokens.at(i) << ",";
  }
  cout << tokens.at(tokens.size()-1) << endl;
  
  return 0;
}
