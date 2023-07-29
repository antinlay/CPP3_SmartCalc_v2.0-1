#include "debit.h"

#include "ui_debit.h"

Debit::Debit(QWidget *parent) : QWidget(parent), ui(new Ui::Debit) {
  auto validator = new QDoubleValidator();

  ui->setupUi(this);
  ui->deposit->setValidator(validator);
  ui->rate->setValidator(validator);
  ui->summDep->setValidator(validator);
  ui->summWithdraw->setValidator(validator);

  ui->casePeriod->addItem("once of week");
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
          [=](const QDate& date) { ui->endDate->setMinimumDate(date);});

  ui->groupBox->setVisible(false);

  connect(ui->buttounCalculate, &QPushButton::clicked, this, &Debit::debitClicked);
}

Debit::~Debit() { delete ui; }

void Debit::debitClicked() {
//  int month = ui->spinBox_months->text().toInt();
//  double sumDep = ui->lineEdit_sumDep->text().toDouble(),
//         percent = ui->lineEdit_intRate->text().toDouble(),
//         resDep = 0, resProfit = 0;
//  bool checkState = ui->checkBox->checkState();
    QDate currentDate = ui->startDate->date(), endDate = ui->endDate->date();
    size_t daysOnYear = currentDate.daysTo(currentDate.addYears(1));

    double deposit = ui->deposit->text().toDouble(), interestRate = ui->rate->text().toDouble()/100/daysOnYear, finalAmount = deposit, profit = 0;
    bool isCapitalized = ui->capitalization->isChecked();

    QString anuInfo;

    /* Формула для вычисления процентов вклада с капитализацией:
Проценты = (Основная сумма * Процентная ставка * Период) / 100

Формула для вычисления процентов вклада без капитализации:
Проценты = (Основная сумма * Процентная ставка * Период) / (12 * 100)

Где:
- Основная сумма - сумма депозита
- Процентная ставка - годовая процентная ставка
- Период - количество месяцев */

    while (currentDate <= endDate) {
        double interest;
        QDate itterator;
        size_t ittWeek = 7;
        if (currentDate.daysTo(endDate) < ittWeek) ittWeek = currentDate.daysTo(endDate);
        if (ui->casePeriod->currentIndex() == 1) itterator = currentDate.addMonths(1);
        if (ui->casePeriod->currentIndex() == 0) itterator = currentDate.addDays(ittWeek);
        if (isCapitalized) {
            interest = finalAmount * interestRate * currentDate.daysTo(itterator);
        } else {
            interest = deposit * interestRate * currentDate.daysTo(itterator);
        }
        finalAmount += interest;
        profit += interest;
        qDebug() << finalAmount;
        qDebug() << profit;

      QString currentYear = QString::number(currentDate.year());
      QString currentMonth = QLocale().monthName(currentDate.month());

      anuInfo += "Pay for " + currentMonth + " " + currentYear + ": " +
                 QString::number(finalAmount, 'f', 2) +
                 " interest: " + QString::number(interest, 'f', 2) + "\n";
      qDebug() << currentDate.daysTo(endDate);
      qDebug() << ittWeek;
      if (ui->casePeriod->currentIndex() == 1) currentDate = currentDate.addMonths(1);
      if (ui->casePeriod->currentIndex() == 0) currentDate = currentDate.addDays(ittWeek);
    }
  qDebug() << daysOnYear;
  ui->profit->clear();
  ui->summ->clear();
  ui->shedule->clear();

  ui->shedule->addItem(anuInfo);
  ui->profit->setText(QString::number(profit, 'f', 2));
  ui->summ->setText(QString::number(finalAmount, 'f', 2));
}
