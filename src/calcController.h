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
  void creditOutputInfo(QString& anuInfo, QString& payment,
                        QString& overpayment)
  //          int caseIndex, double& S, double& i, QDate currentDate,
  //                        size_t n, QString& anuInfo)
  {
    m_->outputCredit(anuInfo, payment, overpayment);
  };
  void outputDebitInfo(QString& anuInfo, QString& summResult, QString& profit);
  void sendDebitUi(Ui::Debit* d) { d_ = d; };
  void sendCrebitUi(Ui::Credit* r) { r_ = r; };

 public:
  CalcController(Ui::CalcView* v, s21::CalcModel* m) : m_(m), v_(v){};
  //  ~CalcController();
  void replaceX(QString& equalResult, QString& equalLabel);
  void validateChangeOn(QString equalStr, bool& status);

 private:
  s21::CalcModel* m_;
  Ui::CalcView* v_;
  Ui::Debit* d_;
  Ui::Credit* r_;
};
}  // namespace s21
#endif  // CALCCONTROLLER_H
