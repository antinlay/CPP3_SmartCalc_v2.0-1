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
  double S = ui->summa->text().toDouble(),
         n = (ui->endDate->date().year() - ui->startDate->date().year()) * 12 +
             ui->endDate->date().month() - ui->startDate->date().month(),
         p = 0, i = QString(ui->percent->text()).toDouble() / 12 / 100;
  qDebug() << n;
  /* Кредитный калькулятор с аннуитетными платежами можно рассчитать по
     следующей формуле: p = (S * i * (1 + i)^n) / ((1 + i)^n - 1)? где: p -
     размер ежемесячного платежа, S - сумма кредита, i - процентная ставка в
     месяц,  n - количество месяцев, O - общая переплата, o - месячная
     переплата, P - обшая переплата */
    QDate currentDate = ui->startDate->date();
    QDate endDate = ui->endDate->date();
  p = (S * (i * qPow((1 + i), n))) / (qPow((1 + i), n) - 1);
  qDebug() << p;
  double P = p * n, O = P - S, o = O / n;
  QString anuInfo;

    while (currentDate <= endDate) {
        QString currentYear = QString::number(currentDate.year());
        QString currentMonth = QLocale().monthName(currentDate.month());
        anuInfo += "Pay for " + currentMonth +
                          " " + currentYear + ": " + QString::number(p, 'f', 2) +
                          " overpayment: " + QString::number(o, 'f', 2) + "\n";

  //         allSum += payment;
  //         summaProc = summa - i * summa / countMonth;
  //         monthPay = QString::number(payment, 'f', 2);

           currentDate = currentDate.addMonths(1);
    }
  // Подсчет количества дней в каждом месяце
  //  while (currentDate <= endDate) {
  //      int year = currentDate.year();
  //      int month = currentDate.month();
  //      int daysInMonth = currentDate.daysInMonth();

  //      qDebug() << "Месяц:" << month << "Год:" << year << "Количество дней:"
  //      << daysInMonth;

  //      // Переход к следующему месяцу
  //      currentDate = currentDate.addMonths(1);
  //  }
  ui->payment->clear();
  ui->overpayment->clear();
  ui->info->clear();

  //  QString stavkaProc,
  //          sumCredit = ui->summa->text(),
  //          spinBox, overPayment, allPayment, result;
  //  size_t comboBox = ui->comboBox->currentIndex();

  //  emit calcCredit(overPayment, allPayment, countMonth, summa,
  //                                            stavkaProc, sumCredit, spinBox,
  //                                            comboBox, result);

  ui->info->addItem(anuInfo);
  ui->payment->setText(QString::number(P,'f', 2));
  ui->overpayment->setText(QString::number(O,'f', 2));
}
