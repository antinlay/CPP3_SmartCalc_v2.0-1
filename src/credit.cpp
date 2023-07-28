#include "credit.h"

#include <cmath>

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

  connect(ui->calculate, &QPushButton::clicked, this, &Credit::calcClicked);

  connect(ui->startDate, &QDateEdit::dateChanged,
          [=](const QDate& date) { ui->endDate->setMinimumDate(date); });
}

Credit::~Credit() { delete ui; }

void Credit::calcClicked() {
  size_t n = (ui->endDate->date().year() - ui->startDate->date().year()) * 12 +
             ui->endDate->date().month() - ui->startDate->date().month(),
         m = 1;
  double S = ui->summa->text().toDouble(),
         i = QString(ui->percent->text()).toDouble() / 12 / 100;

  try {
    if (ui->summa->text().isEmpty() || !n || ui->percent->text().isEmpty()) {
      throw std::invalid_argument("Invalid argument in Credit view!");
    } else {
      QDate currentDate = ui->startDate->date(), endDate = ui->endDate->date();
      QString anuInfo;
      double o = 0, O = 0, p = S, P = i;

      ui->payment->clear();
      ui->overpayment->clear();
      ui->info->clear();

      if (ui->caseCredit->currentIndex() == 0) {
        emit uiEventAnnuityCalc(p, P, n);
        O = P - S;

        while (currentDate <= endDate) {
          QString currentYear = QString::number(currentDate.year());
          QString currentMonth = QLocale().monthName(currentDate.month());

          anuInfo += "Pay for " + currentMonth + " " + currentYear + ": " +
                     QString::number(p, 'f', 2) +
                     " overpayment: " + QString::number(O / n, 'f', 2) + "\n";

          currentDate = currentDate.addMonths(1);
        }
      } else if (ui->caseCredit->currentIndex() == 1) {
        while (m <= n) {
          QString currentYear = QString::number(currentDate.year());
          QString currentMonth = QLocale().monthName(currentDate.month());

//          p = (S / n) + (S - (m - 1) * (S / n)) * i;
//          o = (S - (m - 1) * (S / n)) * i;
          emit uiEventDifferentialCalc(p, o, S, i, n, m);
          P += p;
          O += o;

          anuInfo += "Pay for " + currentMonth + " " + currentYear + ": " +
                     QString::number(p, 'f', 2) +
                     " interest amount: " + QString::number(o, 'f', 2) + "\n";

          currentDate = currentDate.addMonths(1);
          ++m;
        }
      }

      ui->info->addItem(anuInfo);
      ui->payment->setText(QString::number(P, 'f', 2));
      ui->overpayment->setText(QString::number(O, 'f', 2));
    }
  } catch (std::exception& e) {
    QMessageBox::warning(
        this, "Please fill Credit sum, Start-End date, Annual interest rate! ",
        QString::fromStdString(e.what()));
  }
}
