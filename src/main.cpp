#include <cmath>
#include <iostream>
#include <map>
#include <sstream>
#include <stack>
#include <unordered_map>
#include <vector>

// Функция, которая проверяет, является ли символ оператором
bool is_operator(const char& c) {
  static const std::string operators = "+-*/%^";
  return operators.find(c) != std::string::npos;
}

double add(double a, double b) { return a + b; }
double subtract(double a, double b) { return a - b; }
double multiply(double a, double b) { return a * b; }
double divide(double a, double b) {
  if (b == 0) throw std::runtime_error("Error");
  return a / b;
}
double mod(double a, double b) {
  if (b == 0) throw std::runtime_error("Undefined");
  return fmod(a, b);
}
double power(double a, double b) { return pow(a, b); }

double calculate(double a, double b, std::string c) {
  std::map<std::string, double (*)(double, double)> operations = {
      {"+", add},    {"-", subtract}, {"*", multiply},
      {"/", divide}, {"%", mod},      {"^", power}};
  if (!operations[c](a, b))
    throw std::invalid_argument("Input Error");
  else
    return operations[c](a, b);
}

// Return precedence of operators
int precedence(const std::string& c) {
  static const std::unordered_map<std::string, int> precedences = {
      {"+", 1}, {"-", 1}, {"*", 2}, {"/", 2}, {"%", 2}, {"^", 3}, {"(", 0}};
  return precedences.at(c);
}

std::string parser(const std::string& infix) {
  std::string listOperators = "+-*/)(%^";
  std::string str = "";
  for (const char& c : infix) {
    if (listOperators.find(c) == std::string::npos) {
      str += c;
    } else if (!str.empty() && listOperators.find(c) != std::string::npos) {
      str += ' ';
      str += c;
      str += ' ';
    }
  }
  return str;
}

bool isOperator(const std::string& str) {
  std::string listOperators = "+-*/%^";
  bool isOperator = false;
  // char c = str[0];
  if (listOperators.find(str) != std::string::npos) isOperator = true;
  return isOperator;
}

// Infix to postfix
std::vector<std::string> toPostfix(std::stack<std::string>& infix) {
  std::vector<std::string> output;
  std::stack<std::string> s;
  while (!infix.empty()) {
    if (!isOperator(infix.top())) {
      output.push_back(infix.top());
      infix.pop();
    } else if (infix.top() == "(") {
      s.push(infix.top());
      infix.pop();
    } else if (infix.top() == ")") {
      while (!s.empty() || s.top() != "(") {
        output.push_back(s.top());
        s.pop();
      }
      infix.pop();  // Delete ')'
    } else if (isOperator(infix.top())) {
      while (!s.empty() && isOperator(s.top()) &&
             precedence(s.top()) >= precedence(infix.top())) {
        output.push_back(s.top());
        s.pop();
      }
      s.push(infix.top());
      infix.pop();
    }
  }
  // Добавляем оставшиеся операторы в выходную строку
  while (!s.empty()) {
    output.push_back(s.top());
    s.pop();
  }
  return output;
}

int main() {
  std::string infix = "33.4234525+4.1111111*2.0043111/(1.5345119-5.5345119)^2";
  std::istringstream iss(parser(infix));
  std::cout << "Infix: " << parser(infix) << std::endl;
  std::stack<std::string> s;
  std::vector<std::string> postfix;
  std::string element;
  while (iss >> element) {
    s.push(element);
    // std::cout << element << std::endl;
  }
  postfix = toPostfix(s);
  while (!postfix.empty()) {
    std::cout << postfix.back() << std::endl;
    postfix.pop_back();
  }
  return 0;
}
// #include "consoleView.h"

// int main() {
//     ExampleModel model;
//     ExampleController controller(&model);
//     ConsoleView view(&controller);
//     view.startEventLoop();
//     return 1;
// }