#include "debit.h"

Debit::Debit(QWidget* parent) : QWidget(parent), ui(new Ui::Debit) {
  auto validator = new QDoubleValidator(0, std::numeric_limits<int>::max(), 6);

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
          [=]() { initDate(); });

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
  QString anuInfo, summResult, profit;
  try {
    if (ui->deposit->text().isEmpty() || ui->rate->text().isEmpty()) {
      throw std::invalid_argument("Invalid argument in Debit view!");
    } else {
      emit uiEventOutputInfo(anuInfo, summResult, profit);
      // clear fields
      ui->profit->clear();
      ui->summ->clear();
      ui->shedule->clear();
      // add info to fields
      ui->shedule->addItem(anuInfo);
      ui->profit->setText(profit);
      ui->summ->setText(summResult);
    }
  } catch (std::exception& e) {
    QMessageBox::warning(
        this, "Please fill Debit Deposit, Start-End date, interest rate! ",
        QString::fromStdString(e.what()));
  }
}
