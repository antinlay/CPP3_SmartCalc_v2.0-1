#include "credit.h"

#include "ui_credit.h"

Credit::Credit(QWidget* parent) : QWidget(parent), ui(new Ui::Credit) {
  QLocale lo(QLocale::C);
  lo.setNumberOptions(QLocale::RejectGroupSeparator);
  auto val = new QDoubleValidator();
  val->setLocale(lo);

  ui->setupUi(this);

  ui->summa->setValidator(val);
  ui->percent->setValidator(val);

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

  connect(ui->startDate, &QDateEdit::dateChanged,
          [=](const QDate& date) { ui->endDate->setMinimumDate(date.addMonths(1)); });
}

Credit::~Credit() { delete ui; }

void Credit::calcClicked() {
  size_t n = (ui->endDate->date().year() - ui->startDate->date().year()) * 12 +
             ui->endDate->date().month() - ui->startDate->date().month();
  int caseIndex = ui->caseCredit->currentIndex();
  double S = ui->summa->text().toDouble(),
         i = QString(ui->percent->text()).toDouble() / 12 / 100;
  QDate currentDate = ui->startDate->date();
  QString anuInfo;

  try {
    if (ui->summa->text().isEmpty() || !n || ui->percent->text().isEmpty()) {
      throw std::invalid_argument("Invalid argument in Credit view!");
    } else {
        emit uiEventOutputInfo(caseIndex, S, i, currentDate, n, anuInfo);

      // clear fields
      ui->payment->clear();
      ui->overpayment->clear();
      ui->info->clear();
      // add info to fields
      ui->info->addItem(anuInfo);
      ui->payment->setText(QString::number(S, 'f', 2));
      ui->overpayment->setText(QString::number(i, 'f', 2));
    }
  } catch (std::exception& e) {
    QMessageBox::warning(
        this, "Please fill Credit sum, Start-End date, Annual interest rate! ",
        QString::fromStdString(e.what()));
  }
}
