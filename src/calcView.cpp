#include "calcView.h"

CalcView::CalcView(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::CalcView) {
  auto val = new QDoubleValidator();

  ui->setupUi(this);

  ui->resultShow->setValidator(val);
  ui->equalX->setValidator(val);

  graphWindow = new Graph;

  connect(ui->sin, SIGNAL(clicked()), this, SLOT(mathFuncs()));
  connect(ui->cos, SIGNAL(clicked()), this, SLOT(mathFuncs()));
  connect(ui->tan, SIGNAL(clicked()), this, SLOT(mathFuncs()));
  connect(ui->asin, SIGNAL(clicked()), this, SLOT(mathFuncs()));
  connect(ui->acos, SIGNAL(clicked()), this, SLOT(mathFuncs()));
  connect(ui->atan, SIGNAL(clicked()), this, SLOT(mathFuncs()));
  connect(ui->sqrt, SIGNAL(clicked()), this, SLOT(mathFuncs()));
  connect(ui->ln, SIGNAL(clicked()), this, SLOT(mathFuncs()));
  connect(ui->log, SIGNAL(clicked()), this, SLOT(mathFuncs()));
  connect(ui->mod, SIGNAL(clicked()), this, SLOT(mathFuncs()));

  connect(ui->num0, SIGNAL(clicked()), this, SLOT(numFuncs()));
  connect(ui->num1, SIGNAL(clicked()), this, SLOT(numFuncs()));
  connect(ui->num2, SIGNAL(clicked()), this, SLOT(numFuncs()));
  connect(ui->num3, SIGNAL(clicked()), this, SLOT(numFuncs()));
  connect(ui->num4, SIGNAL(clicked()), this, SLOT(numFuncs()));
  connect(ui->num5, SIGNAL(clicked()), this, SLOT(numFuncs()));
  connect(ui->num6, SIGNAL(clicked()), this, SLOT(numFuncs()));
  connect(ui->num7, SIGNAL(clicked()), this, SLOT(numFuncs()));
  connect(ui->num8, SIGNAL(clicked()), this, SLOT(numFuncs()));
  connect(ui->num9, SIGNAL(clicked()), this, SLOT(numFuncs()));

  connect(ui->div, SIGNAL(clicked()), this, SLOT(symbs()));
  connect(ui->mult, SIGNAL(clicked()), this, SLOT(symbs()));
  connect(ui->add, SIGNAL(clicked()), this, SLOT(symbs()));
  connect(ui->sub, SIGNAL(clicked()), this, SLOT(symbs()));
  connect(ui->pow, SIGNAL(clicked()), this, SLOT(symbs()));

  connect(ui->equal, SIGNAL(clicked()), this, SLOT(equalClick()));
  connect(ui->dot, SIGNAL(clicked()), this, SLOT(dotClick()));

  connect(ui->CE, SIGNAL(clicked()), this, SLOT(ceClick()));
  connect(ui->AC, SIGNAL(clicked()), this, SLOT(acClick()));

  connect(ui->graph, SIGNAL(clicked()), this, SLOT(on_graph_clicked()));
  connect(this, &CalcView::sendData, graphWindow, &Graph::getData);
  connect(ui->resultShow, &QLineEdit::textChanged, this, [=]() {
    if (ui->resultShow->text().contains("X", Qt::CaseInsensitive)) {
      ui->equalX->setStyleSheet("border: 1px solid pink;");
      ui->equalX->setEnabled(true);
      ui->graph->setEnabled(true);
    } else {
      ui->equalX->setStyleSheet("");
      ui->equalX->setEnabled(false);
      ui->graph->setEnabled(false);
    }
    if (!resultController.validateChangeOn(ui->resultShow->text())) {
      ui->resultShow->setStyleSheet("border: 1px solid pink;");
      ui->equal->setEnabled(false);
    } else {
      ui->resultShow->setStyleSheet("");
      ui->equal->setEnabled(true);
    }
  });
}

CalcView::~CalcView() { delete ui; }

void CalcView::mathFuncs() {
  QPushButton *button = (QPushButton *)sender();
  QString allStrings;
  allStrings = (ui->resultShow->text() + button->text());
  ui->resultShow->setText(allStrings + '(');
}

void CalcView::numFuncs() {
  QPushButton *button = (QPushButton *)sender();
  QString newString;
  newString = (ui->resultShow->text() + button->text());
  ui->resultShow->setText(newString);
}

void CalcView::symbs() {
  QPushButton *button = (QPushButton *)sender();
  QString allStrings;
  allStrings = (ui->resultShow->text()) + button->text();
  ui->resultShow->setText(allStrings);
}

void CalcView::dotClick() {
  char point = '.';
#ifdef linux
  point = ',';
#endif
  ui->resultShow->setText(ui->resultShow->text() + point);
}

void CalcView::equalClick() {
  QString equalResult = ui->resultShow->text();
  QString equalX = ui->equalX->text();
  resultController.calcExpression(equalResult, equalX);
  ui->resultShow->setText(equalResult);
}

void CalcView::ceClick() {
  if (!ui->resultShow->text().isEmpty()) {
    ui->resultShow->clear();
  }
}

void CalcView::acClick() {
  if (!ui->resultShow->text().isEmpty()) {
    ui->resultShow->backspace();
  }
}

void CalcView::on_credit_clicked() {
  Credit *creditWindow = new Credit();
  creditWindow->show();
}

void CalcView::on_debit_clicked() {
  Debit *debitWindow = new Debit();
  debitWindow->show();
}

void CalcView::on_open_clicked() {
  ui->resultShow->setText(ui->resultShow->text() + "(");
}

void CalcView::on_close_clicked() {
  ui->resultShow->setText(ui->resultShow->text() + ")");
}

void CalcView::on_graph_clicked() {
  if (ui->resultShow->text().contains("X", Qt::CaseInsensitive)) {
    emit sendData(ui->resultShow->text());
    graphWindow->show();
    graphWindow->on_pushButton_clicked();
  }
}

void CalcView::on_xoy_clicked() {
  ui->resultShow->setText(ui->resultShow->text() + "X");
  emit sendData(ui->resultShow->text());
}
