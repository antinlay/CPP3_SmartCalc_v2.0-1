#ifndef CALCVIEW_H
#define CALCVIEW_H

#include <QDoubleValidator>
#include <QMainWindow>
#include <QStack>

//#include "calcController.h"
//#include "credit.h"
//#include "debit.h"
//#include "graph.h"
#include "qobjectdefs.h"
#include "ui_calcView.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class CalcView;
}
QT_END_NAMESPACE

// namespace s21 {
class CalcView : public QMainWindow {
  Q_OBJECT

 public:
  CalcView(QWidget *parent = nullptr);
  ~CalcView();
//  void initCalc();

 signals:
  void sendData(QString res);
  void uiEventOccurred(){};

 private:
  Ui::CalcView *ui;
//  Credit *creditWindow;
//  Debit *debitWindow;
//  Graph *graphWindow;
//  s21::CalcController *c;
  QStack<size_t> textLengthStack;

 private slots:
  QLineEdit* checkActiveLineEdit();
  void equalClick();
  void ceClick();
  void acClick();
  void focusInsert(QString add);
  void on_credit_clicked();
  void on_debit_clicked();
  void on_graph_clicked();
};

// }  // namespace s21
#endif  // CALCVIEW_H
