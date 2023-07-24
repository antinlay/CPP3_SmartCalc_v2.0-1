#include "debit.h"

#include "ui_debit.h"

Debit::Debit(QWidget *parent) : QWidget(parent), ui(new Ui::Debit) {
  auto validator = new QDoubleValidator();

  ui->setupUi(this);
  ui->lineEdit_sumDep->setValidator(validator);
  ui->lineEdit_intRate->setValidator(validator);
}

Debit::~Debit() { delete ui; }

void Debit::on_pushButtonDebit_clicked() {
  int month = ui->spinBox_months->text().toInt();
  double sumDep = ui->lineEdit_sumDep->text().toDouble(),
         percent = ui->lineEdit_intRate->text().toDouble(),
         resDep = 0, resProfit = 0;
  bool checkState = ui->checkBox->checkState();
  
  ui->lineEdit_resDep->clear();
  ui->lineEdit_resPercent->clear();
  ui->listWidget->clear();

//  ui->listWidget->addItem(resultController.calcDebit(
//      resProfit, resDep, sumDep, percent, month, checkState));
  ui->lineEdit_resPercent->setText(QString::number(resProfit, 'f', 2));
  ui->lineEdit_resDep->setText(QString::number(resDep, 'f', 2));
}
