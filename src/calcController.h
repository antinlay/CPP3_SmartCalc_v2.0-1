#ifndef CALCCONTROLLER_H
#define CALCCONTROLLER_H

// #include <QException>
#include <QMainWindow>
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
  void creditOutputInfo(int caseIndex, double& S, double& i, QDate currentDate, size_t n, QString& anuInfo) {
      m_->outputCredit(caseIndex, S, i, currentDate, n, anuInfo);
  };
  void outputDebitInfo(QString summDep, QString summWithdraw, QDate currentDate, QDate endDate, QDate depositDate, QDate withdrawDate, int caseIndex, int caseIndexDep, int caseIndexWithdraw, bool isCapitalized, double deposit, double interestRate, QString& anuInfo) {
      m_->outputDebit(summDep, summWithdraw, currentDate, endDate, depositDate, withdrawDate, caseIndex, caseIndexDep, caseIndexWithdraw, isCapitalized, deposit, interestRate,  anuInfo);
  };

 public:
  CalcController(Ui::CalcView* v, s21::CalcModel* m) : m_(m), v_(v){};
  void replaceX(QString& equalResult, QString& equalLabel);
  void validateChangeOn(QString equalStr, bool& status);
  QString calcDebit(double& resProfit, double& resDep, double sumDep,
                    double percent, int month, bool checkState);

 private:
  s21::CalcModel* m_;
  Ui::CalcView* v_;
};
}  // namespace s21
#endif  // CALCCONTROLLER_H
