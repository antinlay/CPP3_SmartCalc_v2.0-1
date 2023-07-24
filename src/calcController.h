#ifndef CALCCONTROLLER_H
#define CALCCONTROLLER_H

#include <QMainWindow>

#include "calcModel.h"
#include "calcView.h"

namespace s21 {

class CalcController : public QObject {
    Q_OBJECT
public slots:
    void handleUiEvent(){};
 public:
  CalcController(Ui::CalcView *w, s21::CalcModel *m) : m_(m), w_(w){};
  void calcEqual(QString& equalResult, QString& equalX);
  void replaceX(QString& equalResult, QString& equalX);
  bool validateChangeOn(QString equalStr);
  double calcGraph(QString graphResult, double x);
  QString calcCredit(QString& overPayment, QString& allPayment, int month,
                     double summa, QString stavkaProc, QString sumCredit,
                     QString spinBox, size_t comboBox);
  QString calcDebit(double& resProfit, double& resDep, double sumDep,
                    double percent, int month, bool checkState);

 private:
  s21::CalcModel *m_;
  Ui::CalcView *w_;
};
}  // namespace s21
#endif  // CALCCONTROLLER_H
