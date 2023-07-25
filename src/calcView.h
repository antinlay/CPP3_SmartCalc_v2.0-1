#ifndef CALCVIEW_H
#define CALCVIEW_H

#include <QDoubleValidator>
#include <QMainWindow>
#include <QMessageBox>
#include <QStack>

#include "credit.h"
#include "debit.h"
#include "graph.h"
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

 signals:
  void sendData(QString res);
  void uiEventEqual(QString &equalResult, QString &equalLabel);

 private:
  Ui::CalcView *ui;
  Credit *creditWindow;
  Debit *debitWindow;
  Graph *graphWindow;
  QStack<size_t> textLengthStack;
  QLineEdit* lastActiveLineEdit = nullptr;

 private slots:
  void onLineEditFocusChanged(QWidget* oldWidget, QWidget* newWidget)
  {
      QLineEdit* lineEdit = qobject_cast<QLineEdit*>(newWidget);
      if (lineEdit)
      {
          lastActiveLineEdit = lineEdit;
      }
  }
//  void onLineEditCursorPositionChanged()
//  {
//      QLineEdit* lineEdit = qobject_cast<QLineEdit*>(sender());
//      if (lineEdit)
//      {
//          lastActiveLineEdit = lineEdit;
//      }
//  }
  QLineEdit *checkActiveLineEdit();
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
