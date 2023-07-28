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
             ui->endDate->date().month() - ui->startDate->date().month();
  double S = ui->summa->text().toDouble(),
         i = QString(ui->percent->text()).toDouble() / 12 / 100;

  try {
    if (ui->summa->text().isEmpty() || !n || ui->percent->text().isEmpty()) {
      throw std::invalid_argument("Invalid argument in Credit view!");
    } else {
      /* Кредитный калькулятор с аннуитетными платежами можно рассчитать по
         следующей формуле: p = (S * i * (1 + i)^n) / ((1 + i)^n - 1)? где: p -
         размер ежемесячного платежа, S - сумма кредита, i - процентная ставка в
         месяц,  n - количество месяцев, O - общая переплата, o - месячная
         переплата, P - обшая переплата */
      QDate currentDate = ui->startDate->date(), endDate = ui->endDate->date();
      QString anuInfo;
      double m = 1, o = 0, O = 0, p = 0, P = 0;

      ui->payment->clear();
      ui->overpayment->clear();
      ui->info->clear();

      if (ui->caseCredit->currentIndex() == 0) {
        p = (S * (i * qPow((1 + i), n))) / (qPow((1 + i), n) - 1);
        P = p * n;
        O = P - S;
        o = O / n;

        while (currentDate <= endDate) {
          QString currentYear = QString::number(currentDate.year());
          QString currentMonth = QLocale().monthName(currentDate.month());
          anuInfo += "Pay for " + currentMonth + " " + currentYear + ": " +
                     QString::number(p, 'f', 2) +
                     " overpayment: " + QString::number(o, 'f', 2) + "\n";

          currentDate = currentDate.addMonths(1);
        }
      } else if (ui->caseCredit->currentIndex() == 1) {
        /* Формула для расчета дифференцированного платежа выглядит следующим
           образом : P = (S / n) + (S - (m - 1) * (S / n)) * i, где: P - размер
           дифференцированного платежа, S - сумма кредита, n - срок кредита в
           месяцах, m - номер текущего месяца, i - годовая процентная ставка,
           деленная на 12 месяцев. i = (S - (m - 1) * (S / n)) * i */

        while (m <= n) {
          QString currentYear = QString::number(currentDate.year());
          QString currentMonth = QLocale().monthName(currentDate.month());

          p = (S / n) + (S - (m - 1) * (S / n)) * i;
          o = (S - (m - 1) * (S / n)) * i;
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
