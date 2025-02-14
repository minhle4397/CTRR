#ifndef DISCRETE_MATH_HEAD_H
#define DISCRETE_MATH_HEAD_H
#include <iostream>
#include <stack>
#include <string>
#include <algorithm>
#include <sstream>
#include <cctype>
#include <math.h>
#include <iomanip>
using namespace std;
bool isOperator(char c);
bool isBoolOperator(string str);
int getPriority(char c);
int bool_Priority(const string& str);
bool isOperand(char c);
double applyOperator(char op, double operand1, double operand2);
double roundToFourDecimalPlaces(double number);
bool hasOddDecimal(double number);
string removeTrailingZeros(double number);
string removeExtraSpaces(string str);
bool bool_evaluate(bool operand1, bool operand2, string op);
string infixToPostfix(string infix);
string infixToPrefix(string infix);
string PostfixPrefixCalculator(string input);
string bool_infixToPostfix(string infix);
string removeParentheses(const string& input);
string bool_infixToPrefix(string infix);
bool isVariable(const string& str);
string LogicPostfixPrefixCalculator(string input, string varlue);

#endif //DISCRETE_MATH_HEAD_H
