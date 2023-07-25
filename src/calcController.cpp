#include "calcController.h"

// void s21::CalcController::handleUiEvent() {

//}
// QObject::connect(v_, &CalcView::uiEventEqual, m_,
// &s21::CalcController::calcEqual);

void s21::CalcController::replaceX(QString& equalResult, QString& equalX) {
  if (equalResult.contains("X", Qt::CaseInsensitive) && !equalX.isEmpty()) {
    equalResult =
        equalResult.replace("X", "(" + equalX + ")", Qt::CaseInsensitive);
  }
}

void s21::CalcController::calcEqual(QString& equalResult, QString& equalX) {
  try {
    replaceX(equalResult, equalX);
    double result = m_->calculate(equalResult);
    equalResult = QString::number(result, 'g', 14);
  } catch (const std::exception& e) {
    // QMessageBox::critical(reinterpret_cast<QWidget*>(&v_), "Error: ",
    // QString::fromStdString(e.what()));
  }
}

bool s21::CalcController::validateChangeOn(QString equalStr) {
  return m_->validateExpression(equalStr);
}

void s21::CalcController::calcGraph(int& h, double& xStart, double& yStart,
                                    double& xEnd, double& yEnd,
                                    QString graphResult, QVector<double>& x,
                                    QVector<double>& y) {
  m_->graphCalculate(h, xStart, yStart, xEnd, yEnd, graphResult, x, y);
  //  std::cout << "MY X: " << x << "  " << graphResult.toStdString() <<
  //  std::endl;
}

QString s21::CalcController::calcCredit(QString& overPayment,
                                        QString& allPayment, int month,
                                        double summa, QString stavkaProc,
                                        QString sumCredit, QString spinBox,
                                        size_t comboBox) {
  return m_->creditCalculate(overPayment, allPayment, month, summa, stavkaProc,
                             sumCredit, spinBox, comboBox);
}

QString s21::CalcController::calcDebit(double& resProfit, double& resDep,
                                       double sumDep, double percent, int month,
                                       bool checkState) {
  return m_->debitCalculate(resProfit, resDep, sumDep, percent, month,
                            checkState);
}
