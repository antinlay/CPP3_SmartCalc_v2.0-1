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

void s21::CalcController::outputDebitInfo(QString& anuInfo, QString& summResult, QString& profit) {
  m_->setDepStructureValues(
      d_->deposit->text().toDouble(), d_->rate->text().toDouble(),
      d_->casePeriod->currentIndex(), d_->capitalization->isChecked(),
      d_->startDate->date(), d_->endDate->date());
  m_->setReDepStructureValues(d_->summDep->text(), d_->depositDate->date(), d_->casePeriodDep->currentIndex());
  m_->setWithdrawStructureValues(d_->summWithdraw->text(), d_->withdrawDate->date(), d_->casePeriodWithdraw->currentIndex());
  m_->outputDebit(anuInfo, summResult, profit);
}
