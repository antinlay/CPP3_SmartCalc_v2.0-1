#include "calcView.h"

int curs = 0, dot = 0, symb = 0;

CalcView::CalcView(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::CalcView) {
  auto val = new QDoubleValidator();
  // val->setLocale(lo);

  ui->setupUi(this);

  ui->resultShow->setValidator(val);

  // Graph *graphWindow = new Graph();
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
  connect(ui->mod, SIGNAL(clicked()), this, SLOT(symbs()));
  // connect(ui->open, SIGNAL(clicked()), this, SLOT(symbs()));
  // connect(ui->close, SIGNAL(clicked()), this, SLOT(symbs()));

  connect(ui->equal, SIGNAL(clicked()), this, SLOT(equalClick()));
  connect(ui->dot, SIGNAL(clicked()), this, SLOT(dotClick()));

  connect(ui->CE, SIGNAL(clicked()), this, SLOT(ceClick()));
  connect(ui->AC, SIGNAL(clicked()), this, SLOT(acClick()));

  connect(ui->graph, SIGNAL(clicked()), this, SLOT(on_graph_clicked()));
  connect(this, &CalcView::sendData, graphWindow, &Graph::getData);
  connect(ui->resultShow, &QLineEdit::textChanged, this, [=]() {
      if (ui->resultShow->text().contains("X")) {
          ui->equalX->setStyleSheet("border: 1px solid pink;");
          ui->equalX->setEnabled(true);
      } else {
          ui->equalX->setStyleSheet("");
          ui->equalX->setEnabled(false);
      }
      if (!resultModel.validateExpression(ui->resultShow->text().toStdString())) {
          ui->resultShow->setStyleSheet("border: 1px solid pink;");
          ui->equal->setEnabled(false);
      } else {
          ui->resultShow->setStyleSheet("");
          ui->equal->setEnabled(true);
      }
  });
}

CalcView::~CalcView() { delete ui; }

void CalcView::initCalc() {
  if (ui->resultShow->text() == "ERROR") {
    ui->resultShow->clear();
    dot = 0;
    curs = 0;
    symb = 0;
  }
}

void CalcView::mathFuncs() {
  initCalc();
  QPushButton *button = (QPushButton *)sender();
  QString allStrings;
  allStrings = (ui->resultShow->text() + button->text());
  ui->resultShow->setText(allStrings + '(');
  curs++;
  if (dot) dot--;
}

void CalcView::numFuncs() {
  initCalc();
  QPushButton *button = (QPushButton *)sender();
  QString newString;
  newString = (ui->resultShow->text() + button->text());
  ui->resultShow->setText(newString);
  if (symb) symb--;
}

void CalcView::symbs() {
  initCalc();
  QPushButton *button = (QPushButton *)sender();
  QString allStrings;
  if (!symb) {
    allStrings = (ui->resultShow->text()) + button->text();
    ui->resultShow->setText(allStrings);
    symb++;
  }
  if (dot) dot--;
}

void CalcView::dotClick() {
  initCalc();
  if (!dot) {
    char point = '.';
#ifdef linux
    point = ',';
#endif
    ui->resultShow->setText(ui->resultShow->text() + point);
    dot++;
  }
}

void CalcView::equalClick() {
  initCalc();
  std::string str = ui->resultShow->text().toStdString(), num;  // .toStdString
//  CalcController::getExpression(str);
  if (ui->resultShow->text().contains("X", Qt::CaseInsensitive) && !ui->equalX->text().contains("X", Qt::CaseInsensitive)) {
      str = ui->resultShow->text().replace("X",  "(" + ui->equalX->text() + ")").toStdString();
  }
//  if (resultModel.validateExpression(str)) {
      double result = 0;
      result = resultModel.calculate(str);
      QString resCalc = QString::number(result, 'g', 14);
      #ifdef linux
        resCalc.replace('.', ',');
      #endif
      ui->resultShow->setText(resCalc);
      // else {
      //   ui->resultShow->setText("ERROR");
      // }
}

void CalcView::ceClick() {
  if (ui->resultShow->text() != "") {
    ui->resultShow->clear();
  }
  dot = 0;
  symb = 0;
  curs = 0;
}

void CalcView::acClick() {
  initCalc();
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
  initCalc();
  if (!dot) {
    ui->resultShow->setText(ui->resultShow->text() + "(");
  }
}

void CalcView::on_graph_clicked() {
  initCalc();
  if (ui->resultShow->text().contains('X', Qt::CaseInsensitive) &&
      !ui->resultShow->text().contains('=', Qt::CaseInsensitive)) {
    // Graph *graphWindow = new Graph(graphWindow);
    emit sendData(ui->resultShow->text());
    graphWindow->show();
    graphWindow->on_pushButton_clicked();
  } else {
    if (ui->resultShow->text().contains(" X=", Qt::CaseInsensitive)) {
      ui->resultShow->text().replace(" X=", "");
    }
    ui->resultShow->setText(ui->resultShow->text() + "+X");
  }
}

void CalcView::on_xoy_clicked() {
  initCalc();
  if (!dot) {
    ui->resultShow->setText(ui->resultShow->text() + "X");
  }
  symb--;
  emit sendData(ui->resultShow->text());
}

void CalcView::on_close_clicked() {
  initCalc();
  if (!dot) {
    ui->resultShow->setText(ui->resultShow->text() + ")");
  }
}
