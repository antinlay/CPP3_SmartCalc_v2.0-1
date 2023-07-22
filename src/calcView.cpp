#include "calcView.h"

CalcView::CalcView(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::CalcView) {
  //  auto val = new QDoubleValidator();

  ui->setupUi(this);

  //  ui->resultShow->setValidator(val);
  //  ui->equalX->setValidator(val);

  graphWindow = new Graph;

  connect(ui->sin, &QPushButton::clicked, this, [=]() { focusInsert("("); });
  connect(ui->cos, &QPushButton::clicked, this, [=]() { focusInsert("("); });
  connect(ui->tan, &QPushButton::clicked, this, [=]() { focusInsert("("); });
  connect(ui->asin, &QPushButton::clicked, this, [=]() { focusInsert("("); });
  connect(ui->acos, &QPushButton::clicked, this, [=]() { focusInsert("("); });
  connect(ui->atan, &QPushButton::clicked, this, [=]() { focusInsert("("); });
  connect(ui->sqrt, &QPushButton::clicked, this, [=]() { focusInsert("("); });
  connect(ui->ln, &QPushButton::clicked, this, [=]() { focusInsert("("); });
  connect(ui->log, &QPushButton::clicked, this, [=]() { focusInsert("("); });
  connect(ui->mod, &QPushButton::clicked, this, [=]() { focusInsert("("); });

  connect(ui->num0, &QPushButton::clicked, this, [=]() { focusInsert(""); });
  connect(ui->num1, &QPushButton::clicked, this, [=]() { focusInsert(""); });
  connect(ui->num2, &QPushButton::clicked, this, [=]() { focusInsert(""); });
  connect(ui->num3, &QPushButton::clicked, this, [=]() { focusInsert(""); });
  connect(ui->num4, &QPushButton::clicked, this, [=]() { focusInsert(""); });
  connect(ui->num5, &QPushButton::clicked, this, [=]() { focusInsert(""); });
  connect(ui->num6, &QPushButton::clicked, this, [=]() { focusInsert(""); });
  connect(ui->num7, &QPushButton::clicked, this, [=]() { focusInsert(""); });
  connect(ui->num8, &QPushButton::clicked, this, [=]() { focusInsert(""); });
  connect(ui->num9, &QPushButton::clicked, this, [=]() { focusInsert(""); });

  connect(ui->div, &QPushButton::clicked, this, [=]() { focusInsert(""); });
  connect(ui->mult, &QPushButton::clicked, this, [=]() { focusInsert(""); });
  connect(ui->add, &QPushButton::clicked, this, [=]() { focusInsert(""); });
  connect(ui->sub, &QPushButton::clicked, this, [=]() { focusInsert(""); });
  connect(ui->pow, &QPushButton::clicked, this, [=]() { focusInsert(""); });

  connect(ui->open, &QPushButton::clicked, this, [=]() { focusInsert(""); });
  connect(ui->close, &QPushButton::clicked, this, [=]() { focusInsert(""); });
  connect(ui->dot, &QPushButton::clicked, this, [=]() { focusInsert(""); });
  connect(ui->xoy, &QPushButton::clicked, this, [=]() { focusInsert(""); });

  connect(ui->equal, &QPushButton::clicked, this, [=]() { equalClick(); });

  connect(ui->CE, &QPushButton::clicked, this, [=]() { ceClick(); });
  connect(ui->AC, &QPushButton::clicked, this, [=]() { acClick(); });

  connect(ui->graph, &QPushButton::clicked, this,
          [=]() { on_graph_clicked(); });
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

void CalcView::focusInsert(QString add) {
  QPushButton *button = qobject_cast<QPushButton *>(sender());
  QLineEdit *activeLineEdit = qApp->focusWidget()->findChild<QLineEdit *>();
  if (activeLineEdit) {
    // if (ui->resultShow->hasFocus()) {
    // Перенаправление ввода с кнопок на lineEdit1
    // QObject::connect(button, &QPushButton::clicked, ui->resultShow,
    //                  &QLineEdit::setFocus);
    activeLineEdit = ui->resultShow;
    activeLineEdit->insert(button->text() + add);
    // ui->equalX->insert(button->text() + add);
    // } else if (ui->equalX->hasFocus()) {
    // Перенаправление ввода с кнопок на lineEdit2
    // QObject::connect(button, &QPushButton::clicked, ui->equalX,
    //                  &QLineEdit::setFocus);
    // activeLineEdit = ui->equalX;
    // activeLineEdit->insert(button->text() + add);
    // ui->equalX->insert(button->text() + add);
    // }
  }
  // Предположим, что у вас есть активный QLineEdit с именем activeLineEdit
  QString activeLineEditName = activeLineEdit->text();
  qDebug() << "Название активного QLineEdit: " << activeLineEditName;

  // if (activeLineEdit == ui->resultShow) {
  //   ui->resultShow->setFocus();
  // } else if (activeLineEdit == ui->equalX) {
  //   ui->equalX->setFocus();
  // }
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

void CalcView::on_graph_clicked() {
  if (ui->resultShow->text().contains("X", Qt::CaseInsensitive)) {
    emit sendData(ui->resultShow->text());
    graphWindow->show();
    graphWindow->on_pushButton_clicked();
  }
}
