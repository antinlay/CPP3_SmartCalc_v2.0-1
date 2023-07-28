#include "calcController.h"

void s21::CalcController::replaceX(QString& equalResult, QString& equalLabel) {
  if (equalResult.contains("X", Qt::CaseInsensitive) && !equalLabel.isEmpty()) {
    equalResult =
        equalResult.replace("X", "(" + equalLabel + ")", Qt::CaseInsensitive);
  }
}

void s21::CalcController::calcEqual(QString& equalResult, QString& equalLabel) {
  replaceX(equalResult, equalLabel);
  double result = m_->calculate(equalResult);
  equalResult = QString::number(result, 'g', 14);
}

void s21::CalcController::validateChangeOn(QString equalStr, bool& status) {
  status = m_->validateExpression(equalStr);
}

void s21::CalcController::calcGraph(int& h, double& xStart, double& yStart,
                                    double& xEnd, double& yEnd,
                                    QString graphResult, QVector<double>& x,
                                    QVector<double>& y) {
  m_->graphCalculate(h, xStart, yStart, xEnd, yEnd, graphResult, x, y);
}

QString s21::CalcController::calcDebit(double& resProfit, double& resDep,
                                       double sumDep, double percent, int month,
                                       bool checkState) {
  return m_->debitCalculate(resProfit, resDep, sumDep, percent, month,
                            checkState);
}
