#ifndef SRC_CALCMODEL_H
#define SRC_CALCMODEL_H

#include <QtCore/QDate>
#include <QtCore/QQueue>
#include <QtCore/QRegularExpression>
#include <QtCore/QStack>

#include "exprtk.hpp"

namespace s21 {

struct Graph {
  int h;
  double xStart;
  double xEnd;
};

struct Credit {
  double summ;
  double interestRate;
  unsigned short caseIndex;
  QDate currentDate;
  unsigned short months;
};

struct Deposit {
  double summ;
  double interestRate;
  unsigned short caseIndex;
  bool isCapitalized;
  QDate currentDate;
  QDate endDate;
};
struct ReDeposit {
  QString summDep;
  unsigned short caseIndexDep;
  QDate depositDate;
};
struct Withdrawal {
  QString summWithdraw;
  unsigned short caseIndexWithdraw;
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
  void substituteExpr(QString& expression);
  bool validateExpression(QString expression);
  int getPriority(QString c);
  bool isDigital(QChar& currentChar, QString& infix, int& i);
  bool isOperator(const QString& str);
  bool isFunction(const QString& str);
  // MAP CALCULATIONS
  double calcOperations(double a, double b, QString c);
  double calcFunctions(double a, QString c);
  // CONVERT TO POSTFIX
  QQueue<QString> infixToPostfix(QString& infix);
  // CALCULATE POSTFIX
  double getFromStack(QStack<double>& operands);
  double calculatePostfix(QQueue<QString> postfix);
  void replaceX(QString& equalResult, QString& equalLabel);
  double calculate(QString infix);
  QString humanResult(double result);
  // CREDIT CALCULATE
  void outputCredit(QString& anuInfo, QString& payment, QString& overpayment);
  void paymentAnnuityCalc(double& p, double& P);
  void paymentDifferentialCalc(double& p, double& o, size_t m);
  // DEBIT CALCULATE
  void outputDebit(QString& anuInfo, QString& summResult, QString& profit);
  void reDepositWithdrawCalculate(QDate& currentDate, QDate& pasteDate,
                                  QDate& itterator, double& finalAmount,
                                  QString& anuInfo, bool flag);
  void fixDate(QDate& fixDate, unsigned short startCurrentDay);
  void debitCaseMonth(QDate& currentDate, QDate& itterator,
                      unsigned short startCurrentDay);
  void debitCaseWeek(QDate& currentDate, QDate& itterator,
                     unsigned short& ittWeek);
  // GRAPH CALCULATE
  void resizeGraph(QVector<double>& y, double& yStart, double& yEnd);
  void outputGraph(QString& graphResult, QVector<double>& x,
                   QVector<double>& y);

  // DEGREE MODE
  void setUseDegree(bool statusDegreeMode) { useDegree_ = statusDegreeMode; }
  void changeDegreesToRadians(double& a);

  // STRUCT SETTER
  void setGraphStructureValues(int h, double xStart, double xEnd);
  void setCreditStructureValues(double summ, double interestRate,
                                unsigned short caseIndex, QDate currentDate,
                                unsigned short months);
  void setDepStructureValues(double summ, double interestRate,
                             unsigned short caseIndex, bool isCapitalized,
                             QDate currentDate, QDate endDate);
  void setReDepStructureValues(QString summDep, QDate depositDate,
                               unsigned short caseIndexDep);
  void setWithdrawStructureValues(QString summWithdraw, QDate withdrawDate,
                                  unsigned short caseIndexWithdraw);

 private:
  // STRUCTURES
  Graph GraphStruct{};
  Credit CreditStruct{};
  Deposit DepStruct{};
  ReDeposit ReDepositStruct{};
  Withdrawal WithdrawStruct{};
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
#endif  // SRC_CALCMODEL_H
