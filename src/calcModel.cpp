#include "calcModel.h"

// CHECKS
int s21::CalcModel::getPriority(char& c) {
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

bool s21::CalcModel::isOperator(const std::string& str) {
  std::string listOperators = "+-*)(/%^";
  bool result = false;
  if (listOperators.find(str) != std::string::npos) result = true;
  return result;
}

bool s21::CalcModel::isFunction(const std::string& str) {
  std::string listOperators = "qtilncgso";
  bool result = false;
  if (listOperators.find(str) != std::string::npos) result = true;
  return result;
}

// MAP CALCULATIONS
double s21::CalcModel::calcOperations(double a, double b, std::string c) {
  std::map<std::string, std::function<double(s21::CalcModel*, double, double)>>
      operations = {{"+", &s21::CalcModel::addCalc},
                    {"-", &s21::CalcModel::subtractCalc},
                    {"*", &s21::CalcModel::multiplyCalc},
                    {"/", &s21::CalcModel::divideCalc},
                    {"%", &s21::CalcModel::modCalc},
                    {"^", &s21::CalcModel::powerCalc}};
  if (!operations[c](this, a, b))
    throw std::invalid_argument("Input Error");
  else
    return operations[c](this, a, b);
}

double s21::CalcModel::calcFunctions(double a, std::string c) {
  std::map<std::string, std::function<double(s21::CalcModel*, double)>>
      functions = {
          {"q", &s21::CalcModel::sqrtCalc}, {"l", &s21::CalcModel::lnCalc},
          {"g", &s21::CalcModel::logCalc},  {"t", &s21::CalcModel::tanCalc},
          {"n", &s21::CalcModel::atanCalc}, {"s", &s21::CalcModel::sinCalc},
          {"i", &s21::CalcModel::asinCalc}, {"c", &s21::CalcModel::cosCalc},
          {"o", &s21::CalcModel::acosCalc}};
  if (!functions[c](this, a))
    throw std::invalid_argument("Input Error");
  else
    return functions[c](this, a);
}

// CONVERT TO POSTFIX
std::queue<std::string> s21::CalcModel::infixToPostfix(std::string& infix) {
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
        if (i == 0) operatorStack.push(infix.substr(i, 1));
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

  return outputQueue;
}

// CALCULATE POSTFIX
double s21::CalcModel::getFromStack(std::stack<double>& operands) {
  double operand = operands.top();
  operands.pop();
  return operand;
}

double s21::CalcModel::calculatePostfix(std::queue<std::string> postfix) {
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

// int main(void) {
//   s21::CalcModel ll;
//   std::string infix = "-5+(-1+2)*4*c(-2*7.5-2)+s(c(2*5))-q(2^g(5-1))+l(55)";
//   std::queue<std::string> newInfix = ll.infixToPostfix(infix);
//   std::cout << "Result: " << ll.calculatePostfix(newInfix) << std::endl;
//   printf("%f", ll.calculatePostfix(newInfix));
//   return 0;
// }