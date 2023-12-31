#ifndef CALCVIEW_H
#define CALCVIEW_H

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
  CalcView(QWidget* parent = nullptr);
  ~CalcView();
  void setLineEdit(QLineEdit* ActiveLineEdit) {
    lastActiveLineEdit_ = ActiveLineEdit;
  };

 signals:
  void validateChangedOn(QString expression, bool& status);

  void uiEventReplaceX(QString& resultShow, QString& equalX);
  void uiEventEqual(QString& equalResult, QString& equalLabel);
  void uiEventSendResult(QString equalResult);

  void uiEventShowCredit();
  void uiEventShowDebit();
  void uiEventSendUi(Ui::CalcView* v);

 private slots:
  QLineEdit* checkActiveLineEdit();
  void onLineEditFocusChanged(QWidget* newWidget);
  void equalClick();
  void ceClick();
  void acClick();
  void focusInsert();
  void creditClicked();
  void debitClicked();
  void graphClicked();

 private:
  Ui::CalcView* ui = nullptr;
  QStack<size_t> textLengthStack{};
  bool status_ = false;
  QLineEdit* lastActiveLineEdit_ = nullptr;
};

// }  // namespace s21
#endif  // CALCVIEW_H
