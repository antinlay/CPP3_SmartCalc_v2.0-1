#include "calcController.h"

void s21::CalcController::sendCalcViewUi(Ui::CalcView* v) {
  v_ = v;
  setDegreeMode();
};

void s21::CalcController::setDegreeMode() {
  m_->setUseDegree(v_->radioButton->isChecked());
};

void s21::CalcController::replaceX(QString& equalResult, QString& equalLabel) {
  m_->replaceX(equalResult, equalLabel);
}

void s21::CalcController::calcEqual(QString& equalResult, QString& equalLabel) {
  replaceX(equalResult, equalLabel);
  double result = m_->calculate(equalResult);
  equalResult = m_->humanResult(result);
}

void s21::CalcController::validateChangeOn(QString equalStr, bool& status) {
  status = m_->validateExpression(equalStr);
}

void s21::CalcController::graphOutput(QString& graphResult, QVector<double>& x,
                                      QVector<double>& y) {
  m_->setGraphStructureValues(g_->caseBox->value(),
                              g_->doubleSpinBox_xStart->value(),
                              g_->doubleSpinBox_xEnd->value());
  m_->outputGraph(graphResult, x, y);
}

void s21::CalcController::graphResize(QVector<double>& y, double& yStart,
                                      double& yEnd) {
  m_->resizeGraph(y, yStart, yEnd);
}

void s21::CalcController::outputDebitInfo(QString& anuInfo, QString& summResult,
                                          QString& profit) {
  m_->setDepStructureValues(
      d_->deposit->text().toDouble(), d_->rate->text().toDouble(),
      d_->casePeriod->currentIndex(), d_->capitalization->isChecked(),
      d_->startDate->date(), d_->endDate->date());
  m_->setReDepStructureValues(d_->summDep->text(), d_->depositDate->date(),
                              d_->casePeriodDep->currentIndex());
  m_->setWithdrawStructureValues(d_->summWithdraw->text(),
                                 d_->withdrawDate->date(),
                                 d_->casePeriodWithdraw->currentIndex());
  m_->outputDebit(anuInfo, summResult, profit);
}

void s21::CalcController::creditOutputInfo(QString& anuInfo, QString& payment,
                                           QString& overpayment) {
  unsigned short months =
      (r_->endDate->date().year() - r_->startDate->date().year()) * 12 +
      r_->endDate->date().month() - r_->startDate->date().month();
  m_->setCreditStructureValues(
      r_->summa->text().toDouble(), r_->percent->text().toDouble(),
      r_->caseCredit->currentIndex(), r_->startDate->date(), months);
  m_->outputCredit(anuInfo, payment, overpayment);
};
