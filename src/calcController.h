#ifndef CALCCONTROLLER_H
#define CALCCONTROLLER_H

#include <QMainWindow>

#include "calcModel.h"

namespace s21 {

class CalcController {
 public:
  void calcExpression(QString& equalResult, QString& equalX);
  bool validateChangeOn(QString equalStr);
  double calcGraph(QString graphResult, double x);
  QString calcCredit(QString& overPayment, QString& allPayment, int month,
                     double summa, QString stavkaProc, QString sumCredit,
                     QString spinBox, size_t comboBox);
  QString calcDebit(double& resProfit, double& resDep, double sumDep,
                    double percent, int month, bool checkState);

 private:
  s21::CalcModel resultModel;
};
}  // namespace s21
#endif  // CALCCONTROLLER_H
