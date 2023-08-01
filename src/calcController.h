#ifndef CALCCONTROLLER_H
#define CALCCONTROLLER_H

#include <QMessageBox>
#include <QWidget>

#include "calcModel.h"
#include "calcView.h"
#include "credit.h"
#include "debit.h"

namespace s21 {

class CalcController : public QObject {
  Q_OBJECT

 public slots:
  void calcEqual(QString& equalResult, QString& equalLabel);
  void calcGraph(int& h, double& xStart, double& yStart, double& xEnd,
                 double& yEnd, QString graphResult, QVector<double>& x,
                 QVector<double>& y);
  void setDegreeMode(bool statusDegreeMode) {
    m_->setDegreeMode(statusDegreeMode);
  };
  void creditOutputInfo(int caseIndex, double& S, double& i, QDate currentDate,
                        size_t n, QString& anuInfo) {
    m_->outputCredit(caseIndex, S, i, currentDate, n, anuInfo);
  };

  void outputDebitInfo(QString& anuInfo, QString& summResult, QString& profit) {
    m_->setDepStructureValues(
        d_->deposit->text().toDouble(), d_->rate->text().toDouble(),
        d_->casePeriod->currentIndex(), d_->capitalization->isChecked(),
        d_->startDate->date(), d_->endDate->date());
    m_->setReDepStructureValues(d_->summDep->text(), d_->depositDate->date(), d_->casePeriodDep->currentIndex());
    m_->setWithdrawStructureValues(d_->summWithdraw->text(), d_->withdrawDate->date(), d_->casePeriodWithdraw->currentIndex());
    m_->outputDebit(anuInfo, summResult, profit);
  }

 public:
  CalcController(Ui::CalcView* v, s21::CalcModel* m) : m_(m), v_(v){};
  void replaceX(QString& equalResult, QString& equalLabel);
  void validateChangeOn(QString equalStr, bool& status);
  QString calcDebit(double& resProfit, double& resDep, double sumDep,
                    double percent, int month, bool checkState);

QObject::connect(d_, &Debit::uiEventOutputInfo, c_, &CalcController::outputDebitInfo);
QObject::connect(v_, &CalcView::uiEventShowDebit, d_, &Debit::showDedit);

 private:
  CalcController* c_;
  s21::CalcModel* m_;
  Ui::CalcView* v_;
  Ui::Debit* d_;
};
}  // namespace s21
#endif  // CALCCONTROLLER_H
