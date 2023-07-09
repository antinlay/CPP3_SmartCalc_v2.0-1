#include "calcModel.h"

// CHECKS
int s21::CalcModel::getPriority(std::string c) {
  int res = 0;
  if (isFunction(c)) {
    res = 4;
  } else {
    res = precedences.at(c);
  }
  return res;
}

bool s21::CalcModel::isDigit(char& currentChar, std::string& infix, int& i) {
  bool result = false;
  if (isdigit(currentChar) || currentChar == '.' || currentChar == 'e' ||
      (currentChar == '-' &&
       (i == 0 || !isdigit(infix[i - 1]) && infix[i - 1] != ')'))) {
    result = true;
  }
  return result;
}

bool s21::CalcModel::isOperator(const std::string& str) {
  std::string listOperators = "+-*)(/%^";
  bool result = false;
  if (listOperators.find(str) != std::string::npos) result = true;
  return result;
}

bool s21::CalcModel::isFunction(const std::string& str) {
  std::string listOperators = "qgaiontsc";
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
  if (operations.find(c) == operations.end())
    throw std::invalid_argument("Input Error: " + c + " not found");
  else
    return operations[c](this, a, b);
}

double s21::CalcModel::calcFunctions(double a, std::string c) {
  std::map<std::string, std::function<double(s21::CalcModel*, double)>>
      functions = {
          {"q", &s21::CalcModel::sqrtCalc}, {"n", &s21::CalcModel::lnCalc},
          {"g", &s21::CalcModel::logCalc},  {"t", &s21::CalcModel::tanCalc},
          {"a", &s21::CalcModel::atanCalc}, {"s", &s21::CalcModel::sinCalc},
          {"i", &s21::CalcModel::asinCalc}, {"c", &s21::CalcModel::cosCalc},
          {"o", &s21::CalcModel::acosCalc}};
  if (functions.find(c) == functions.end())
    throw std::invalid_argument("Input Error: " + c + "not found");
  else
    return functions[c](this, a);
}

void s21::CalcModel::fixInfix(std::string& infix) {
  static const std::unordered_map<std::string, std::string> keyFunctions = {
      {"sqrt", "q"}, {"ln", "n"},   {"log", "g"}, {"tan", "t"}, {"atan", "a"},
      {"sin", "s"},  {"asin", "i"}, {"cos", "c"}, {"acos", "o"}};
  for (auto& key : keyFunctions) {
    size_t pos = 0;
    while ((pos = infix.find(key.first, pos)) != std::string::npos) {
      infix.replace(pos, key.first.length(), key.second);
      pos += key.second.length();
    }
  }
}

// CONVERT TO POSTFIX
std::queue<std::string> s21::CalcModel::infixToPostfix(std::string& infix) {
  std::stack<std::string> operatorStack;
  std::queue<std::string> outputQueue;
  std::string currentToken = "";

  infix.append(")");
  operatorStack.push("(");

  for (int i = 0; i < infix.length(); ++i) {
    printf("SYMB: %c\n", infix[i]);
    if (isdigit(infix[i])) {
      if (currentToken.length() == 0) {
        currentToken += infix[i];
      } else if (isdigit(currentToken[0]) || currentToken[0] == '.' ||
                 currentToken[0] == '+' || currentToken[0] == '-' ||
                 currentToken[0] == 'e') {
        currentToken += infix[i];
      } else {
        if (isFunction(currentToken)) {
          operatorStack.push(currentToken);
        }
        currentToken = infix[i];
      }
    } else if (isOperator(std::string(1, infix[i]))) {
      if (currentToken.empty() && (infix[i] == '+' || infix[i] == '-') &&
          !isFunction(outputQueue.back())) {
        currentToken += infix[i];
        continue;
      } else {
        if (isFunction(currentToken)) {
          operatorStack.push(currentToken);
        } else if (currentToken.length() > 0) {
          outputQueue.push(currentToken);
        }
        currentToken.clear();
      }
      while (!operatorStack.empty() && operatorStack.top() != "(" &&
             !isFunction(operatorStack.top()) &&
             getPriority(std::string(1, infix[i])) <=
                 getPriority(operatorStack.top()) &&
             infix[i] != '^') {
        outputQueue.push(operatorStack.top());
        operatorStack.pop();
      }
      operatorStack.push(std::string(1, infix[i]));
    } else if (infix[i] == '(') {
      operatorStack.push(std::string(1, infix[i]));
    } else if (infix[i] == ')') {
      while (!operatorStack.empty() && operatorStack.top() != "(") {
        if (!currentToken.empty()) {
          if (isFunction(currentToken)) {
            operatorStack.push(currentToken);
          } else {
            outputQueue.push(currentToken);
          }
          currentToken.clear();
        }
        outputQueue.push(operatorStack.top());
        operatorStack.pop();
      }
      if (!operatorStack.empty() && operatorStack.top() == "(") {
        operatorStack.pop();
      } else {
        std::cout << "Error: incomplite right paranthesis at position "
                  << (i + 1) << std::endl;
        std::exit(1);
      }
      if (!operatorStack.empty() && isFunction(operatorStack.top())) {
        outputQueue.push(operatorStack.top());
        operatorStack.pop();
      }
    } else {
      if (!currentToken.empty() &&
          (isdigit(currentToken[0]) || currentToken[0] == '.' ||
           currentToken[0] == '+' || currentToken[0] == '-' ||
           currentToken[0] == 'e')) {
        if (infix[i] == '.') {
          currentToken += infix[i];
        } else {
          outputQueue.push(currentToken);
          currentToken = infix[i];
        }
      } else if (isFunction(currentToken)) {
        operatorStack.push(currentToken);
        currentToken = infix[i];
      } else {
        currentToken += infix[i];
      }
    }
  }

  // for (int i = 0; i < infix.length(); ++i) {
  //   char currentChar = infix[i];
  //   if (currentChar == '(') {
  //     operatorStack.push("(");
  //   }
  //   if (isDigit(currentChar, infix, i)) {
  //     while (isDigit(currentChar, infix, i)) {
  //       currentToken.append(std::string(1, currentChar));
  //       currentChar = infix[++i];
  //     }
  //     outputQueue.push(currentToken);
  //     currentToken.clear();
  //   }
  //   if (currentChar == ')') {
  //     while (!operatorStack.empty() && operatorStack.top() != "(") {
  //       outputQueue.push(operatorStack.top());
  //       operatorStack.pop();
  //     }
  //     if (operatorStack.top() == "(") operatorStack.pop();
  //   }
  //   if (isOperator(std::string(1, currentChar))) {
  //     while (!operatorStack.empty() && operatorStack.top() != "(" &&
  //            getPriority(std::string(1, currentChar)) <=
  //                getPriority(operatorStack.top())) {
  //       outputQueue.push(operatorStack.top());
  //       operatorStack.pop();
  //     }
  //     operatorStack.push(std::string(1, currentChar));
  //   }
  // }

  // for (int i = 0; i < infix.length(); i++) {
  //   char currentChar = infix[i];
  //   if (isDigit(currentChar, infix, i)) {
  //     if (currentChar == 'e') {
  //       currentToken += currentChar;
  //       currentChar = infix[++i];
  //     }
  //     currentToken += currentChar;
  //   } else {
  //     if (!currentToken.empty()) {
  //       outputQueue.push(currentToken);
  //       currentToken = "";
  //     }
  //     if (currentChar == '(') {
  //       operatorStack.push(std::string(1, currentChar));
  //     } else if (currentChar == ')') {
  //       while (operatorStack.top() != "(") {
  //         outputQueue.push(operatorStack.top());
  //         operatorStack.pop();
  //       }
  //       operatorStack.pop();
  //       // } else if (isFunction(infix.substr(i, 1))) {
  //       //   if (i == 0) operatorStack.push(infix.substr(i, 1));
  //     } else {
  //       while (!operatorStack.empty() && operatorStack.top() != "(" &&
  //              getPriority(std::string(1, currentChar)) <=
  //                  getPriority(operatorStack.top())) {
  //         outputQueue.push(operatorStack.top());
  //         operatorStack.pop();
  //       }
  //       operatorStack.push(std::string(1, currentChar));
  //     }
  //   }
  // }

  if (!currentToken.empty()) {
    outputQueue.push(currentToken);
  }

  while (!operatorStack.empty()) {
    // if (operatorStack.top() == "(") {
    //   std::cout << "Error: mismatched paranthesis";
    //   std::exit(1);
    // }
    outputQueue.push(operatorStack.top());
    operatorStack.pop();
  }
  std::cout << std::endl;

  return outputQueue;
}

// CALCULATE POSTFIX
double s21::CalcModel::getFromStack(std::stack<double>& operands) {
  double operand = 0;
  if (!operands.empty()) {
    operand = operands.top();
    operands.pop();
  }
  return operand;
}

double s21::CalcModel::calculatePostfix(std::queue<std::string> postfix) {
  std::stack<double> calcStack;
  std::string token;

  while (!postfix.empty()) {
    token = postfix.front();
    std::cout << token << " ";
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

double s21::CalcModel::calculate(std::string infix) {
  std::queue<std::string> newInfix = infixToPostfix(infix);
  return calculatePostfix(newInfix);
}

int main(void) {
  s21::CalcModel ll;
  std::string infix = "51+2";
  ll.fixInfix(infix);
  std::cout << "fixInfix: " << infix << std::endl;
  std::queue<std::string> newInfix = ll.infixToPostfix(infix);
  std::cout << "Result: " << ll.calculatePostfix(newInfix) << std::endl;
  // std::cout << "5 -1 - 2 + 4 * c 2 7.5 * - 2 - * + s c 2 5 * +" << std::endl;
  printf("\n%f", ll.calculatePostfix(newInfix));

  return 0;
}
