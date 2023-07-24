#include "calcController.h"

void s21::CalcController::replaceX(QString& equalResult,
                                         QString& equalX) {
  if (equalResult.contains("X", Qt::CaseInsensitive) && !equalX.isEmpty()) {
    equalResult =
        equalResult.replace("X", "(" + equalX + ")", Qt::CaseInsensitive);
  }
}

void s21::CalcController::calcEqual(QString& equalResult, QString& equalX) {
    replaceX(equalResult,equalX);
    double result = m_->calculate(equalResult);
    equalResult = QString::number(result, 'g', 14);
}

bool s21::CalcController::validateChangeOn(QString equalStr) {
  return m_->validateExpression(equalStr);
}

double s21::CalcController::calcGraph(QString graphResult, double x) {
  QString num = QString::number(x);
  graphResult.replace("X", num, Qt::CaseInsensitive);

  double result = m_->calculate(graphResult);
  return result;
}

QString s21::CalcController::calcCredit(QString& overPayment,
                                        QString& allPayment, int month,
                                        double summa, QString stavkaProc,
                                        QString sumCredit, QString spinBox,
                                        size_t comboBox) {
  return m_->creditCalculate(overPayment, allPayment, month, summa,
                                     stavkaProc, sumCredit, spinBox, comboBox);
}

QString s21::CalcController::calcDebit(double& resProfit, double& resDep,
                                       double sumDep, double percent, int month,
                                       bool checkState) {
  return m_->debitCalculate(resProfit, resDep, sumDep, percent, month,
                                    checkState);
}
