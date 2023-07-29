#include "debit.h"

#include "ui_debit.h"

Debit::Debit(QWidget *parent) : QWidget(parent), ui(new Ui::Debit) {
  auto validator = new QDoubleValidator();

  ui->setupUi(this);
  ui->deposit->setValidator(validator);
  ui->rate->setValidator(validator);
  ui->summDep->setValidator(validator);
  ui->summWithdraw->setValidator(validator);

  ui->casePeriod->addItem("once");
  ui->casePeriod->addItem("once of month");

  ui->casePeriodDep->addItem("once");
  ui->casePeriodDep->addItem("once of month");

  ui->casePeriodWithdraw->addItem("once");
  ui->casePeriodWithdraw->addItem("once of month");

  ui->startDate->setDisplayFormat("dd.MM.yyyy");
  ui->endDate->setDisplayFormat("dd.MM.yyyy");

  ui->depositDate->setDisplayFormat("dd.MM.yyyy");
  ui->withdrawDate->setDisplayFormat("dd.MM.yyyy");

  ui->startDate->setCalendarPopup(true);
  ui->startDate->setDate(QDate::currentDate());

  ui->endDate->setCalendarPopup(true);
  ui->endDate->setDate(QDate::currentDate());

  ui->depositDate->setCalendarPopup(true);
  ui->depositDate->setDate(QDate::currentDate());

  ui->withdrawDate->setCalendarPopup(true);
  ui->withdrawDate->setDate(QDate::currentDate());

  connect(ui->startDate, &QDateEdit::dateChanged,
          [=](const QDate& date) { ui->endDate->setMinimumDate(date);
  ui->depositDate->setMinimumDate(date);
  ui->depositDate->setMinimumDate(date);});
}

Debit::~Debit() { delete ui; }

void Debit::debitClicked() {
//  int month = ui->spinBox_months->text().toInt();
//  double sumDep = ui->lineEdit_sumDep->text().toDouble(),
//         percent = ui->lineEdit_intRate->text().toDouble(),
//         resDep = 0, resProfit = 0;
//  bool checkState = ui->checkBox->checkState();
  
  ui->profit->clear();
  ui->summ->clear();
  ui->shedule->clear();

//  ui->listWidget->addItem(resultController.calcDebit(
//      resProfit, resDep, sumDep, percent, month, checkState));
//  ui->lineEdit_resPercent->setText(QString::number(resProfit, 'f', 2));
//  ui->lineEdit_resDep->setText(QString::number(resDep, 'f', 2));
}
