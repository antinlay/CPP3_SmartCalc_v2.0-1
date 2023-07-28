#ifndef CALCMODEL_H
#define CALCMODEL_H

#include <QCoreApplication>
#include <QException>
#include <QMainWindow>
#include <QQueue>
#include <QRegularExpressionValidator>
#include <QStack>
#include <QTextStream>
#include <QValidator>
#include <cmath>
#include <iostream>

namespace s21 {

class CalcModel {
 public:
  CalcModel() = default;
  ~CalcModel() = default;

 public:
  // OPERATIONS
  double addCalc(double a, double b);
  double subtractCalc(double a, double b);
  double multiplyCalc(double a, double b);
  double divideCalc(double a, double b);
  double modCalc(double a, double b);
  double powerCalc(double a, double b);
  double sqrtCalc(double a);

  // FUNCTIONS
  double lnCalc(double a);
  double logCalc(double a);
  double tanCalc(double a);
  double atanCalc(double a);
  double sinCalc(double a);
  double asinCalc(double a);
  double cosCalc(double a);
  double acosCalc(double a);

  // CHECKS
  bool validateExpression(QString& expression);
  int getPriority(QString c);
  bool isDigit(QChar& currentChar, QString& infix, int& i);
  bool isOperator(const QString& str);
  bool isFunction(const QString& str);
  // MAP CALCULATIONS
  double calcOperations(double a, double b, QString c);
  double calcFunctions(double a, QString c);
  // CONVERT TO POSTFIX
  void fixInfix(QString& infix);
  QQueue<QString> infixToPostfix(QString& infix);
  // CALCULATE POSTFIX
  double getFromStack(QStack<double>& operands);
  double calculatePostfix(QQueue<QString> postfix);
  double calculate(QString infix);
  // CREDIT CALCULATE
  double paymentAnnuityCalc(double S, double i, size_t n);
  double overpaymentAnnuityCalc(double S, double i, size_t n);
  QString debitCalculate(double& resProfit, double& resDep, double sumDep,
                         double percent, int month, bool checkState);
  void graphCalculate(int& h, double& xStart, double& yStart, double& xEnd,
                      double& yEnd, QString graphResult, QVector<double>& x,
                      QVector<double>& y);

  // DEGREE MODE
  void setDegreeMode(bool statusDegreeMode) { useDegree_ = statusDegreeMode; }
  double changeDegreesToRadians(double& a) {
    if (useDegree_) {
      a = qDegreesToRadians(a);
    }
    return a;
  };

 private:
  bool useDegree_ = false;
  QMap<QString, int> precedences_ = {{"(", 0}, {")", 0}, {"+", 1}, {"-", 1},
                                     {"*", 2}, {"/", 2}, {"%", 2}, {"^", 3}};
  const QHash<QString, QString> keyFunctions = {
      {"sqrt", "q"}, {"ln", "n"},  {"log", "g"},  {"tan", "t"},
      {"atan", "a"}, {"sin", "s"}, {"asin", "i"}, {"cos", "c"},
      {"acos", "o"}, {"mod", "%"}, {"x", "X"}};
};  // namespace s21
}  // namespace s21
#endif  // CALCMODEL_H
