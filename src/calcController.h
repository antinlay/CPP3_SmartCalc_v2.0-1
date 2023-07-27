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

 public:
  CalcController(Ui::CalcView* v, s21::CalcModel* m) : m_(m), v_(v){};
  void replaceX(QString& equalResult, QString& equalLabel);
  void validateChangeOn(QString equalStr, bool& status);
  void calcCredit(QString& overPayment, QString& allPayment, int month,
                  double summa, QString stavkaProc, QString sumCredit,
                  QString spinBox, size_t comboBox, QString& result);
  QString calcDebit(double& resProfit, double& resDep, double sumDep,
                    double percent, int month, bool checkState);

 private:
  s21::CalcModel* m_;
  Ui::CalcView* v_;
};
}  // namespace s21
#endif  // CALCCONTROLLER_H
