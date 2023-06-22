#ifndef CALCVIEW_H
#define CALCVIEW_H

#include <QMainWindow>

#include "calcController.h"
#include "credit.h"
#include "debit.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class calcView;
}
QT_END_NAMESPACE

class calcView : public QMainWindow {
  Q_OBJECT

 public:
  calcView(QWidget *parent = nullptr);
  ~calcView();
  void initCalc();

 signals:
  void sendData(QString res);

 private:
  Ui::calcView *ui;
  Credit *creditWindow;
  Debit *debitWindow;
  // graph *graphWindow;
 private slots:
  void mathFuncs();
  void numFuncs();
  void symbs();
  void dotClick();
  //   void equalClick();
  void ceClick();
  void acClick();
  void on_credit_clicked();
  void on_debit_clicked();
  //   void on_open_clicked();
  //   void on_graph_clicked();
  //   void on_xoy_clicked();
  //   void on_close_clicked();
};
#endif  // CALCVIEW_H
