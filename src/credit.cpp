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
}

Credit::~Credit() { delete ui; }

void Credit::on_pushButtonCredit_clicked() {
  int month = ui->spinBox->text().toInt();
  double summa = ui->lineEdit_sumCredit->text().toDouble();

  ui->lineEdit_sumVyplat->clear();
  ui->lineEdit_sumPereplata->clear();
  ui->listWidget->clear();

  QString stavkaProc = ui->lineEdit_stavkaProc->text(),
          sumCredit = ui->lineEdit_sumCredit->text(),
          spinBox = ui->spinBox->text(), overPayment, allPayment;
  size_t comboBox = ui->comboBox->currentIndex();

  //  ui->listWidget->addItem(
  //      resultController.calcCredit(overPayment, allPayment, month, summa,
  //                                  stavkaProc, sumCredit, spinBox,
  //                                  comboBox));
  ui->lineEdit_sumVyplat->setText(allPayment);
  ui->lineEdit_sumPereplata->setText(overPayment);
}
