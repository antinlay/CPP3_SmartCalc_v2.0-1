#include "credit.h"

#include "ui_credit.h"

Credit::Credit(QWidget* parent) : QWidget(parent), ui(new Ui::Credit) {
  auto validator = new QDoubleValidator(0, std::numeric_limits<int>::max(), 6);

  ui->setupUi(this);

  ui->summa->setValidator(validator);
  ui->percent->setValidator(validator);

  ui->caseCredit->addItem("annuity");
  ui->caseCredit->addItem("differentiated");

  ui->startDate->setDisplayFormat("dd.MM.yyyy");
  ui->endDate->setDisplayFormat("dd.MM.yyyy");
  ui->startDate->setCalendarPopup(true);
  ui->startDate->setDate(QDate::currentDate());

  ui->endDate->setCalendarPopup(true);
  ui->endDate->setDate(QDate::currentDate());

  ui->endDate->setMinimumDate(ui->startDate->date().addMonths(1));

  connect(ui->calculate, &QPushButton::clicked, this, &Credit::calcClicked);

  connect(ui->startDate, &QDateEdit::dateChanged, [=]() {
    ui->endDate->setMinimumDate(ui->startDate->date().addMonths(1));
  });
}

Credit::~Credit() { delete ui; }

void Credit::calcClicked() {
  try {
    if (ui->summa->text().isEmpty() || ui->percent->text().isEmpty()) {
      throw std::invalid_argument("Invalid argument in Credit view!");
    } else {
      QString anuInfo, summResult, profit;

      emit uiEventOutputInfo(anuInfo, summResult, profit);

      // clear fields
      ui->payment->clear();
      ui->overpayment->clear();
      ui->info->clear();
      // add info to fields
      ui->info->addItem(anuInfo);
      ui->payment->setText(summResult);
      ui->overpayment->setText(profit);
    }
  } catch (std::exception& e) {
    QMessageBox::warning(
        this, "Please fill Credit sum, Start-End date, Annual interest rate! ",
        QString::fromStdString(e.what()));
  }
}
