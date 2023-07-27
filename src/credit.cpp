#include "credit.h"

#include <cmath>

#include "ui_credit.h"

Credit::Credit(QWidget *parent) : QWidget(parent), ui(new Ui::Credit) {
  QLocale lo(QLocale::C);
  lo.setNumberOptions(QLocale::RejectGroupSeparator);
  auto val = new QDoubleValidator();
  val->setLocale(lo);

  ui->setupUi(this);

  ui->lineEdit_sumCredit->setValidator(val);
  ui->lineEdit_stavkaProc->setValidator(val);

  ui->comboBox->addItem("annuity");
  ui->comboBox->addItem("differentiated");

  ui->startDate->setDisplayFormat("dd.MM.yyyy");
  ui->endDate->setDisplayFormat("dd.MM.yyyy");

  ui->startDate->setCalendarPopup(true);
  ui->startDate->setDate(QDate::currentDate());

  ui->endDate->setCalendarPopup(true);
  ui->endDate->setDate(QDate::currentDate());

  connect(ui->startDate, &QDateEdit::dateChanged, [=](const QDate& date) {
          ui->endDate->setMinimumDate(date);
      });

}

Credit::~Credit() { delete ui; }

void Credit::on_pushButtonCredit_clicked() {
  double summa = ui->lineEdit_sumCredit->text().toDouble(), countMonth = (ui->endDate->date().year() - ui->startDate->date().year()) * 12 + ui->endDate->date().month() - ui->startDate->date().month();
  qDebug() << countMonth;
  QDate currentDate = ui->startDate->date();
  QDate endDate = ui->endDate->date();
  while (currentDate <= endDate) {
      QString currentYear = QString::number(currentDate.year());
      QString currentMonth = QLocale().monthName(currentDate.month());

         payment = summa / countMonth + summaProc * stavka * 31 / 365 / 100;
         allSum += payment;
         summaProc = summa - i * summa / countMonth;
         monthPay = QString::number(payment, 'f', 2);
         payInfo = "Pay for " + currentMonth+ " " + currentYear + " month = " + monthPay + "\n";
         currentDate = currentDate.addMonths(1);
  }
  // Подсчет количества дней в каждом месяце
  while (currentDate <= endDate) {
      int year = currentDate.year();
      int month = currentDate.month();
      int daysInMonth = currentDate.daysInMonth();

      qDebug() << "Месяц:" << month << "Год:" << year << "Количество дней:" << daysInMonth;

      // Переход к следующему месяцу
      currentDate = currentDate.addMonths(1);
  }
  ui->lineEdit_sumVyplat->clear();
  ui->lineEdit_sumPereplata->clear();
  ui->listWidget->clear();

  QString stavkaProc = ui->lineEdit_stavkaProc->text(),
          sumCredit = ui->lineEdit_sumCredit->text(),
          spinBox, overPayment, allPayment, result;
  size_t comboBox = ui->comboBox->currentIndex();

  emit calcCredit(overPayment, allPayment, countMonth, summa,
                                            stavkaProc, sumCredit, spinBox,
                                            comboBox, result);

  ui->listWidget->addItem(result);

  ui->lineEdit_sumVyplat->setText(allPayment);
  ui->lineEdit_sumPereplata->setText(overPayment);
}
