#ifndef CALCCONTROLLER_H
#define CALCCONTROLLER_H

#include "calcModel.h"
#include "calcView.h"
#include "credit.h"
#include "debit.h"

namespace s21 {

class CalcController : public QObject {
  Q_OBJECT

 public slots:
  void calcEqual(QString& equalResult, QString& equalLabel);
  void graphOutput(QString& graphResult, QVector<double>& x,
                   QVector<double>& y);
  void graphResize(QVector<double>& y, double& yStart, double& yEnd);
  void setDegreeMode();
  void creditOutputInfo(QString& anuInfo, QString& payment,
                        QString& overpayment);
  void outputDebitInfo(QString& anuInfo, QString& summResult, QString& profit);
  void sendDebitUi(Ui::Debit* d) { d_ = d; };
  void sendCreditUi(Ui::Credit* r) { r_ = r; };
  void sendGraphUi(Ui::Graph* g) { g_ = g; };
  void sendCalcViewUi(Ui::CalcView* v) {
    v_ = v;
    setDegreeMode();
  };

 public:
  CalcController(s21::CalcModel* m, Ui::CalcView* v) : m_(m), v_(v){};
  void replaceX(QString& equalResult, QString& equalLabel);
  void validateChangeOn(QString equalStr, bool& status);

 private:
  s21::CalcModel* m_ = nullptr;
  Ui::CalcView* v_ = nullptr;
  Ui::Graph* g_ = nullptr;
  Ui::Debit* d_ = nullptr;
  Ui::Credit* r_ = nullptr;
};
}  // namespace s21
#endif  // CALCCONTROLLER_H
