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
  Debit(QWidget *parent = nullptr);
  ~Debit();
   void showDebit() {this->show(); emit uiEventSendUi(ui);};

 signals:
//   void uiEventOutputInfo(QString summDep, QString summWithdraw, QDate currentDate, QDate endDate, QDate depositDate, QDate withdrawDate, int caseIndex, int caseIndexDep, int caseIndexWithdraw, bool isCapitalized, double deposit, double interestRate, QString& anuInfo);
   void uiEventOutputInfo(QString& anuInfo, QString& summResult, QString& profit);
   void uiEventSendUi(Ui::Debit* d);

 private slots:
  void debitClicked();
  void initDate();
//  void addHBoxLayout() {
//      QGroupBox *groupBox = new QGroupBox("GroupBox");
//      QHBoxLayout *hBoxLayout = new QHBoxLayout;
//      groupBox->setLayout(hBoxLayout);
//      QVBoxLayout *layout = qobject_cast<QVBoxLayout*>(centralWidget()->layout());
//      layout->addWidget(groupBox);

//      QPushButton *deleteButton = new QPushButton("Удалить QHBoxLayout");
//      connect(deleteButton, &QPushButton::clicked, [hBoxLayout, groupBox]() {
//          groupBox->layout()->removeItem(hBoxLayout);
//          delete hBoxLayout;
//          delete deleteButton;
//          groupBox->adjustSize();
//      });
//      hBoxLayout->addWidget(deleteButton);
//      groupBox->adjustSize();
//  };
  
 private:
  Ui::Debit *ui;

};

// }  // namespace s21

#endif  // DEBIT_H
