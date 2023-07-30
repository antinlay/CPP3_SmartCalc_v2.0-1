#include "debit.h"

#include "ui_debit.h"

Debit::Debit(QWidget* parent) : QWidget(parent), ui(new Ui::Debit) {
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
          [=](const QDate& date) { ui->endDate->setMinimumDate(date); });

  ui->groupBox->setVisible(false);

  connect(ui->buttounCalculate, &QPushButton::clicked, this,
          &Debit::debitClicked);
}

Debit::~Debit() { delete ui; }

void Debit::debitClicked() {
  QDate currentDate = ui->startDate->date(), endDate = ui->endDate->date();
  size_t daysOnYear = currentDate.daysTo(currentDate.addYears(1));

  double deposit = ui->deposit->text().toDouble(),
         interestRate = ui->rate->text().toDouble() / 100 / daysOnYear,
         finalAmount = deposit, profit = 0;
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
  auto currentDay = currentDate.day();
  while (currentDate.daysTo(endDate) > 0) {
    double interest;
    auto ittWeek = 7;
    QDate itterator;
    if (ui->casePeriod->currentIndex() == 1) {
      currentDate = currentDate.addMonths(1);
      if (currentDate.month() != 2) currentDate.setDate(currentDate.year(), currentDate.month(), currentDay);
      itterator = currentDate.addMonths(1);
      if (itterator.month() != 2) itterator.setDate(itterator.year(), itterator.month(), currentDay);
    }
    if (ui->casePeriod->currentIndex() == 0) {
      if (currentDate.daysTo(endDate) <= ittWeek) {
        ittWeek = currentDate.daysTo(endDate);
      }
      currentDate = currentDate.addDays(ittWeek);
      itterator = currentDate.addDays(ittWeek);
    }
    if (isCapitalized) {
        qDebug() << currentDate.daysTo(itterator) << "CD to ITT";
      interest = finalAmount * interestRate * currentDate.daysTo(itterator);
      qDebug() << interest << "CD to ITT";
    } else {
      interest = deposit * interestRate * currentDate.daysTo(itterator);
    }
    finalAmount += interest;
    profit += interest;
    qDebug() << finalAmount << "FA";
    qDebug() << profit << "PR";

    QString currentYear = QString::number(currentDate.year());
    QString currentMonth = QLocale().monthName(currentDate.month());
    QString currentDay = QString::number(currentDate.day());

    anuInfo += "Pay for " + currentDay + " " + currentMonth + " " +
               currentYear + ": " + QString::number(finalAmount, 'f', 2) +
               " interest: " + QString::number(interest, 'f', 2) + "\n";
    qDebug() << currentDate.daysTo(endDate) << "CR - ED";
    qDebug() << ittWeek << "ITT";
  }
  qDebug() << daysOnYear;
  ui->profit->clear();
  ui->summ->clear();
  ui->shedule->clear();

  ui->shedule->addItem(anuInfo);
  ui->profit->setText(QString::number(profit, 'f', 2));
  ui->summ->setText(QString::number(finalAmount, 'f', 2));
}
