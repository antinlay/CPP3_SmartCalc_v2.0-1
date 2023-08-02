#ifndef CALCMODEL_H
#define CALCMODEL_H

#include <QCoreApplication>
#include <QDate>
#include <QException>
#include <QMainWindow>
#include <QQueue>
#include <QRegularExpressionValidator>
#include <QStack>
#include <QTextStream>
#include <QValidator>
#include <iostream>

namespace s21 {

struct Credit {
  double summ;
  double interestRate;
  short caseIndex;
  QDate currentDate;
  short months;
};

struct Deposit {
  double summ;
  double interestRate;
  short caseIndex;
  bool isCapitalized;
  QDate currentDate;
  QDate endDate;
};
struct ReDeposit {
  QString summDep;
  short caseIndexDep;
  QDate depositDate;
};
struct Withdrawal {
  QString summWithdraw;
  short caseIndexWithdraw;
  QDate withdrawDate;
};

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
  void outputCredit(QString& anuInfo, QString& payment, QString& overpayment);
  void paymentAnnuityCalc(double& p, double& P);
  void paymentDifferentialCalc(double& p, double& o, size_t m);
  // DEBIT CALCULATE
  void outputDebit(QString& anuInfo, QString& summResult, QString& profit);
  void graphCalculate(int& h, double& xStart, double& yStart, double& xEnd,
                      double& yEnd, QString graphResult, QVector<double>& x,
                      QVector<double>& y);
  void reDepositWithdrawCalculate(QDate& currentDate, QDate& pasteDate,
                                  QDate& itterator, double& finalAmount,
                                  QString& anuInfo, bool flag);
  void fixDate(QDate& fixDate, short startCurrentDay);
  void debitCaseMonth(QDate& currentDate, QDate& itterator, short startCurrentDay);
  void debitCaseWeek(QDate& currentDate, QDate& itterator, short& ittWeek);

  // DEGREE MODE
  void setDegreeMode(bool statusDegreeMode) { useDegree_ = statusDegreeMode; }
  void changeDegreesToRadians(double& a) {
    if (useDegree_) {
      a = qDegreesToRadians(a);
    }
  };

  // STRUCT GET-SET
  Deposit getDepStructure() { return DepStruct; };
  void setDepStructureValues(double summ, double interestRate, short caseIndex,
                             bool isCapitalized, QDate currentDate,
                             QDate endDate) {
    DepStruct.summ = summ;
    DepStruct.interestRate = interestRate;
    DepStruct.caseIndex = caseIndex;
    DepStruct.isCapitalized = isCapitalized;
    DepStruct.currentDate = currentDate;
    DepStruct.endDate = endDate;
  }
  ReDeposit getReDepStructure() { return ReDepositStruct; };
  void setReDepStructureValues(QString summDep, QDate depositDate,
                               short caseIndexDep) {
    ReDepositStruct.summDep = summDep;
    ReDepositStruct.depositDate = depositDate;
    ReDepositStruct.caseIndexDep = caseIndexDep;
  }
  Withdrawal getWithdrawStructure() { return WithdrawStruct; };
  void setWithdrawStructureValues(QString summWithdraw, QDate withdrawDate,
                                  short caseIndexWithdraw) {
    WithdrawStruct.summWithdraw = summWithdraw;
    WithdrawStruct.withdrawDate = withdrawDate;
    WithdrawStruct.caseIndexWithdraw = caseIndexWithdraw;
  }

 private:
  // STRUCTURES
  Credit CreditStruct;
  Deposit DepStruct;
  ReDeposit ReDepositStruct;
  Withdrawal WithdrawStruct;
  // DEGREE FLAG
  bool useDegree_ = false;
  // OPERATORS && FUNCTIONS
  QMap<QString, int> precedences_ = {{"(", 0}, {")", 0}, {"+", 1}, {"-", 1},
                                     {"*", 2}, {"/", 2}, {"%", 2}, {"^", 3}};
  const QHash<QString, QString> keyFunctions = {
      {"sqrt", "q"}, {"ln", "n"},  {"log", "g"},  {"tan", "t"},
      {"atan", "a"}, {"sin", "s"}, {"asin", "i"}, {"cos", "c"},
      {"acos", "o"}, {"mod", "%"}, {"x", "X"}};
};
}  // namespace s21
#endif  // CALCMODEL_H
