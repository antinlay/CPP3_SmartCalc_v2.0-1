#include "calcController.h"

void s21::CalcController::calcExpression(QString& equalResult,
                                         QString& equalX) {
  if (equalResult.contains("X", Qt::CaseInsensitive) &&
      !equalX.contains("X", Qt::CaseInsensitive)) {
    equalResult =
        equalResult.replace("X", "(" + equalX + ")", Qt::CaseInsensitive);
  }
  double result = resultModel.calculate(equalResult.toStdString());
  equalResult = QString::number(result, 'g', 14);
}

bool s21::CalcController::validateChangeOn(QString equalStr) {
  return resultModel.validateExpression(equalStr.toStdString());
}

double s21::CalcController::calcGraph(QString graphResult, double x) {
  QString num = QString::number(x);
  graphResult.replace("X", num, Qt::CaseInsensitive);

  double result = resultModel.calculate(graphResult.toStdString());
  return result;
}

QString s21::CalcController::calcCredit(QString& overPayment,
                                        QString& allPayment, int month,
                                        double summa, QString stavkaProc,
                                        QString sumCredit, QString spinBox,
                                        size_t comboBox) {
  return resultModel.creditCalculate(overPayment, allPayment, month, summa,
                                     stavkaProc, sumCredit, spinBox, comboBox);
}

QString s21::CalcController::calcDebit(double& resProfit, double& resDep,
                                       double sumDep, double percent, int month,
                                       bool checkState) {
  return resultModel.debitCalculate(resProfit, resDep, sumDep, percent, month,
                                    checkState);
}