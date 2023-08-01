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

  initDate();

  ui->groupBoxDep->setVisible(false);
  ui->groupBoxWithdraw->setVisible(false);

  connect(ui->startDate, &QDateEdit::dateChanged,
          [=](const QDate& date) { initDate(); });

  connect(ui->buttounCalculate, &QPushButton::clicked, this,
          &Debit::debitClicked);

  connect(ui->addDeposit, &QPushButton::clicked, this,
          [=]() { ui->groupBoxDep->setVisible(true); });
  connect(ui->addWithdraw, &QPushButton::clicked, this,
          [=]() { ui->groupBoxWithdraw->setVisible(true); });
}

Debit::~Debit() { delete ui; }

void Debit::initDate() {
  ui->endDate->setMinimumDate(ui->startDate->date().addMonths(1));
  ui->depositDate->setMinimumDate(ui->startDate->date().addMonths(1));
  ui->withdrawDate->setMinimumDate(ui->startDate->date().addMonths(1));
}

void Debit::debitClicked() {
//  QDate currentDate = ui->startDate->date(), endDate = ui->endDate->date(),
//        depositDate = ui->depositDate->date(),
//        withdrawDate = ui->withdrawDate->date();
//  size_t daysOnYear = currentDate.daysTo(currentDate.addYears(1));

//  double deposit = ui->deposit->text().toDouble(),
//         interestRate = ui->rate->text().toDouble() / 100 / daysOnYear,
//         finalAmount = deposit, profit = 0;
//  bool isCapitalized = ui->capitalization->isChecked();

  QString anuInfo, summResult, profit;
emit uiEventOutputInfo(anuInfo, summResult, profit);
  /* Формула для вычисления процентов вклада с капитализацией:
Проценты = (Основная сумма * Процентная ставка * Период) / 100

Формула для вычисления процентов вклада без капитализации:
Проценты = (Основная сумма * Процентная ставка * Период) / (12 * 100)
Где:
- Основная сумма - сумма депозита
- Процентная ставка - годовая процентная ставка
- Период - количество месяцев */
//  auto startCurrentDay = currentDate.day(), startDepDay = depositDate.day(),
//       startWithdrawDay = withdrawDate.day();

//  while (currentDate.daysTo(endDate) > 0) {
//    double interest;
//    auto ittWeek = 7;
//    QDate itterator;
//    if (ui->casePeriod->currentIndex() == 1) {
//      currentDate = currentDate.addMonths(1);
//      if (currentDate.month() != 2 || startCurrentDay == 31)
//        currentDate.setDate(currentDate.year(), currentDate.month(),
//                            currentDate.daysInMonth());
//      itterator = currentDate.addMonths(1);
//      if (itterator.month() != 2 || startCurrentDay == 31)
//        itterator.setDate(itterator.year(), itterator.month(),
//                          itterator.daysInMonth());
//    }
//    if (ui->casePeriod->currentIndex() == 0) {
//      if (currentDate.daysTo(endDate) <= ittWeek) {
//        ittWeek = currentDate.daysTo(endDate);
//      }
//      currentDate = currentDate.addDays(ittWeek);
//      itterator = currentDate.addDays(ittWeek);
//    }
//    if (isCapitalized) {
//      qDebug() << currentDate.daysTo(itterator) << "CD to ITT";
//      interest = finalAmount * interestRate * currentDate.daysTo(itterator);
//      qDebug() << interest << "CD to ITT";
//    } else {
//      interest = deposit * interestRate * currentDate.daysTo(itterator);
//    }
//    finalAmount += interest;
//    profit += interest;
//    qDebug() << finalAmount << "FA";
//    qDebug() << profit << "PR";

//    QString currentYear = QString::number(currentDate.year());
//    QString currentMonth = QLocale().monthName(currentDate.month());
//    QString currentDay = QString::number(currentDate.day());

//    anuInfo += "Pay for " + currentDay + " " + currentMonth + " " +
//               currentYear + ": " + QString::number(finalAmount, 'f', 2) +
//               " interest: " + QString::number(interest, 'f', 2) + "\n";
//    qDebug() << currentDate.daysTo(endDate) << "CR - ED";
//    qDebug() << ittWeek << "ITT";

//    if (!ui->summDep->text().isEmpty()) {
//      if (ui->casePeriodDep->currentIndex() == 0 ||
//          ui->casePeriodDep->currentIndex() == 1) {
//        if (currentDate <= depositDate && itterator >= depositDate &&
//            endDate >= depositDate) {
//          finalAmount += ui->summDep->text().toDouble();
//          anuInfo += "Deposite for " + QString::number(depositDate.day()) +
//                     " " + QLocale().monthName(depositDate.month()) + " " +
//                     QString::number(depositDate.year()) + ": " +
//                     QString::number(finalAmount, 'f', 2) + " amount: " +
//                     QString::number(ui->summDep->text().toDouble(), 'f', 2) +
//                     "\n";
//          if (ui->casePeriodDep->currentIndex() == 1) {
//            depositDate = depositDate.addMonths(1);
//            if (depositDate.month() != 2 || startDepDay == 31)
//              depositDate.setDate(depositDate.year(), depositDate.month(),
//                                  depositDate.daysInMonth());
//          }
//        }
//      }
//    }

//    if (!ui->summWithdraw->text().isEmpty()) {
//      if (ui->casePeriodWithdraw->currentIndex() == 0 ||
//          ui->casePeriodWithdraw->currentIndex() == 1) {
//        if (currentDate <= withdrawDate && itterator >= withdrawDate &&
//            endDate >= withdrawDate) {
//          if (finalAmount > ui->summWithdraw->text().toDouble()) {
//            finalAmount -= ui->summWithdraw->text().toDouble();
//            anuInfo +=
//                "Withdraw for " + QString::number(withdrawDate.day()) + " " +
//                QLocale().monthName(withdrawDate.month()) + " " +
//                QString::number(withdrawDate.year()) + ": " +
//                QString::number(finalAmount, 'f', 2) + " amount: " +
//                QString::number(ui->summWithdraw->text().toDouble(), 'f', 2) +
//                "\n";
//            if (ui->casePeriodWithdraw->currentIndex() == 1) {
//              withdrawDate = withdrawDate.addMonths(1);
//              if (withdrawDate.month() != 2 || startWithdrawDay == 31)
//                withdrawDate.setDate(withdrawDate.year(), withdrawDate.month(),
//                                     withdrawDate.daysInMonth());
//            }
//          }
//        }
//      }
//    }
//  }
  ui->profit->clear();
  ui->summ->clear();
  ui->shedule->clear();

  ui->shedule->addItem(anuInfo);
  ui->profit->setText(profit);
  ui->summ->setText(summResult);
}
