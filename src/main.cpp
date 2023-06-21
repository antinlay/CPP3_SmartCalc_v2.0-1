#include <cmath>
#include <iostream>
#include <list>
#include <map>
#include <queue>
#include <sstream>
#include <stack>
#include <unordered_map>

double addCalc(double a, double b) { return a + b; }
double subtractCalc(double a, double b) { return a - b; }
double multiplyCalc(double a, double b) { return a * b; }
double divideCalc(double a, double b) {
  if (b == 0) throw std::runtime_error("Error divide zero");
  return a / b;
}
double modCalc(double a, double b) {
  if (b == 0) throw std::runtime_error("Undefined");
  return fmod(a, b);
}
double powerCalc(double a, double b) { return pow(a, b); }

double sqrtCalc(double a) { return sqrt(a); }
double lnCalc(double a) { return log(a); }
double logCalc(double a) { return log10(a); }
double tanCalc(double a) { return tan(a); }
double atanCalc(double a) { return atan(a); }
double sinCalc(double a) { return sin(a); }
double asinCalc(double a) { return asin(a); }
double cosCalc(double a) { return cos(a); }
double acosCalc(double a) { return acos(a); }

double calcOperations(double a, double b, std::string c) {
  std::map<std::string, double (*)(double, double)> operations = {
      {"+", addCalc},    {"-", subtractCalc}, {"*", multiplyCalc},
      {"/", divideCalc}, {"%", modCalc},      {"^", powerCalc}};
  if (!operations[c](a, b))
    throw std::invalid_argument("Input Error");
  else
    return operations[c](a, b);
}

double calcFunctions(double a, std::string c) {
  std::map<std::string, double (*)(double)> functions = {
      {"q", sqrtCalc}, {"l", lnCalc},   {"g", logCalc},
      {"t", tanCalc},  {"n", atanCalc}, {"s", sinCalc},
      {"i", asinCalc}, {"c", cosCalc},  {"o", acosCalc}};
  if (!functions[c](a))
    throw std::invalid_argument("Input Error");
  else
    return functions[c](a);
}

bool isFunction(const std::string& str) {
  std::string listOperators = "qtilncgso";
  bool result = false;
  if (listOperators.find(str) != std::string::npos) result = true;
  return result;
}

// Return priority of operators
int getPriority(char& c) {
  int res = 0;
  if (isFunction(std::string(1, c))) {
    res = 4;
  } else {
    static const std::unordered_map<char, int> precedences = {
        {'+', 1}, {'-', 1}, {'*', 2}, {'/', 2},
        {'%', 2}, {'^', 3}, {'(', 0}, {')', 0}};
    res = precedences.at(c);
  }
  return res;
}

bool isOperator(const std::string& str) {
  std::string listOperators = "+-*)(/%^";
  bool result = false;
  if (listOperators.find(str) != std::string::npos) result = true;
  return result;
}

// Infix to postfix
std::queue<std::string> infixToPostfix(std::string& infix) {
  std::stack<std::string> operatorStack;
  std::queue<std::string> outputQueue;
  std::string currentToken = "";

  for (int i = 0; i < infix.length(); i++) {
    char currentChar = infix[i];
    if (isdigit(currentChar) || currentChar == '.' || currentChar == 'e') {
      if (currentChar == 'e') {
        currentToken += currentChar;
        currentChar = infix[++i];
      }
      currentToken += currentChar;
    } else {
      if (!currentToken.empty()) {
        outputQueue.push(currentToken);
        currentToken = "";
      }

      if (currentChar == '(') {
        operatorStack.push(std::string(1, currentChar));
      } else if (currentChar == ')') {
        while (operatorStack.top() != "(") {
          outputQueue.push(operatorStack.top());
          operatorStack.pop();
        }
        operatorStack.pop();
      } else if (isFunction(infix.substr(i, 1))) {
        operatorStack.push(infix.substr(i, 1));
      } else {
        while (!operatorStack.empty() && operatorStack.top() != "(" &&
               getPriority(currentChar) <=
                   getPriority(operatorStack.top()[0])) {
          outputQueue.push(operatorStack.top());
          operatorStack.pop();
        }
        operatorStack.push(std::string(1, currentChar));
      }
    }
  }

  if (!currentToken.empty()) {
    outputQueue.push(currentToken);
  }

  while (!operatorStack.empty()) {
    outputQueue.push(operatorStack.top());
    operatorStack.pop();
  }

  // std::string postfixExpression = "";
  // while (!outputQueue.empty()) {
  //   postfixExpression += outputQueue.front() + " ";
  //   outputQueue.pop();
  // }

  return outputQueue;
}

double getFromStack(std::stack<double>& operands) {
  double operand = operands.top();
  operands.pop();
  return operand;
}

double calculatePostfix(std::queue<std::string> postfix) {
  std::stack<double> calcStack;
  std::string token;
  while (!postfix.empty()) {
    token = postfix.front();
    postfix.pop();
    if (isOperator(token)) {
      double operand1 = getFromStack(calcStack);
      double operand2 = getFromStack(calcStack);
      double result = calcOperations(operand2, operand1, token);
      calcStack.push(result);
    } else if (isFunction(token)) {
      double topStack = getFromStack(calcStack);
      double debug = calcFunctions(topStack, token);
      calcStack.push(debug);
    } else {
      double debug = std::stod(token);
      calcStack.push(debug);
    }
  }
  return calcStack.top();
}

int main() {
  // double a = 13123.113;
  // double b = 0.113;
  // std::string c = "%";
  // double res = calcOperations(a, b, c);
  // std::cout << res << std::endl;

  std::string infix =
      "33.4234525+4.1111111*2.0043111/"
      "(1.5345119-5.5345119)^2-g(1-0.5)-123.11e-5";
  std::queue<std::string> newInfix = infixToPostfix(infix);

  // std::istringstream iss(apendDelimeter(infix));
  // std::cout << "Postfix: " << newInfix << std::endl;

  std::cout << "Result: " << calculatePostfix(newInfix) << std::endl;
  printf("%f", calculatePostfix(newInfix));

  // std::list<std::string> s = stringToList(newInfix);
  // std::list<std::string> postfix = infixToPostfix(s);
  // std::string element;
  // while (iss >> element) {
  //   s.push_back(element);
  //   // std::cout << element << std::endl;
  // }
  // while (!postfix.empty()) {
  //   std::cout << postfix.front() << std::endl;
  //   postfix.pop_front();
  // }
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