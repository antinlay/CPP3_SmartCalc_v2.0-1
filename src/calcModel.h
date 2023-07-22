#ifndef CALCMODEL_H
#define CALCMODEL_H

#include <QMainWindow>
#include <QValidator>
#include <cmath>
#include <functional>
#include <iostream>
#include <map>
#include <queue>
#include <regex>
#include <stack>
#include <unordered_map>

namespace s21 {

class CalcModel {
 public:
  CalcModel() = default;
  ~CalcModel() = default;

 public:
  // OPERATIONS
  double addCalc(double a, double b) { return a + b; }
  double subtractCalc(double a, double b) { return a - b; }
  double multiplyCalc(double a, double b) { return a * b; }
  double divideCalc(double a, double b) {
    if (b == 0)
      throw std::runtime_error("Undefined divide zero: " + std::to_string(a) +
                               "/" + std::to_string(b));
    else
      return a / b;
  }
  double modCalc(double a, double b) {
    // if (b == 0)
    //   throw std::runtime_error("Undefined mod(" + std::to_string(a) + ", " +
    //                            std::to_string(b) + ")");
    // else
    return fmod(a, b);
  }
  double powerCalc(double a, double b) { return pow(a, b); }

  double sqrtCalc(double a) { return sqrt(abs(a)); }
  // FUNCTIONS
  double lnCalc(double a) { return log(a); }
  double logCalc(double a) { return log10(a); }
  double tanCalc(double a) { return tan(a); }
  double atanCalc(double a) { return atan(a); }
  double sinCalc(double a) { return sin(a); }
  double asinCalc(double a) { return asin(a); }
  double cosCalc(double a) { return cos(a); }
  double acosCalc(double a) { return acos(a); }
  // CHECKS
  bool validateExpression(QString& expression);
  int getPriority(std::string c);
  bool isDigit(char& currentChar, std::string& infix, int& i);
  bool isOperator(const std::string& str);
  bool isFunction(const std::string& str);
  // MAP CALCULATIONS
  double calcOperations(double a, double b, std::string c);
  double calcFunctions(double a, std::string c);
  // CONVERT TO POSTFIX
  void fixInfix(std::string& infix);
  std::queue<std::string> infixToPostfix(std::string& infix);
  // CALCULATE POSTFIX
  double getFromStack(std::stack<double>& operands);
  double calculatePostfix(std::queue<std::string> postfix);
  double calculate(std::string infix);
  QString creditCalculate(QString& overPayment, QString& allPayment, int month,
                          double summa, QString stavkaProc, QString sumCredit,
                          QString spinBox, size_t comboBox);
  QString debitCalculate(double& resProfit, double& resDep, double sumDep,
                         double percent, int month, bool checkState);

 private:
  std::unordered_map<std::string, int> precedences = {
      {"(", 0}, {")", 0}, {"+", 1}, {"-", 1},
      {"*", 2}, {"/", 2}, {"%", 2}, {"^", 3}};
};
}  // namespace s21
#endif  // CALCMODEL_H
