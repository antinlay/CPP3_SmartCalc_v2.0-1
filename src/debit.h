#ifndef DEBIT_H
#define DEBIT_H

#include <QMessageBox>

#include "ui_debit.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class Debit;
}
QT_END_NAMESPACE

// namespace s21 {
class Debit : public QWidget {
  Q_OBJECT

 public:
  Debit(QWidget* parent = nullptr);
  ~Debit();
  void showDebit() {
    this->show();
    emit uiEventSendUi(ui);
  };

 signals:
  void uiEventOutputInfo(QString& anuInfo, QString& summResult,
                         QString& profit);
  void uiEventSendUi(Ui::Debit* d);

 private slots:
  void debitClicked();
  void initDate();

 private:
  Ui::Debit* ui;
};

// }  // namespace s21

#endif  // DEBIT_H
