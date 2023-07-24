#include "calcView.h"

CalcView::CalcView(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::CalcView) {
  //  auto val = new QDoubleValidator();

  ui->setupUi(this);

  //  ui->resultShow->setValidator(val);
  //  ui->equalX->setValidator(val);

  //  graphWindow = new Graph;

  //  connect(ui->equal, &QPushButton::clicked, c, c->handleUIEvent());

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
  //  connect(this, &CalcView::sendData, graphWindow, &Graph::getData);
  connect(ui->equalX, &QLineEdit::textChanged, this, [=]() {
    if (ui->equalX->text().contains("X", Qt::CaseInsensitive)) {
      ui->equal->setEnabled(false);
    } else {
      ui->equal->setEnabled(true);
    }
  });
  connect(ui->resultShow, &QLineEdit::textChanged, this, [=]() {
    if (ui->resultShow->text().contains("X", Qt::CaseInsensitive)) {
      ui->enterX->setEnabled(true);
      if (ui->enterX->isEnabled()) {
        ui->equalX->setStyleSheet("border: 1px solid pink;");
        ui->equalX->setEnabled(true);
        ui->graph->setEnabled(true);
      }
    } else {
      ui->enterX->setEnabled(false);
      ui->equalX->setStyleSheet("");
      ui->equalX->setEnabled(false);
      ui->graph->setEnabled(false);
    }
    //    if (!resultController.validateChangeOn(ui->resultShow->text())) {
    //      ui->resultShow->setStyleSheet("border: 1px solid pink;");
    //      ui->equal->setEnabled(false);
    //    } else {
    //      ui->resultShow->setStyleSheet("");
    //      ui->equal->setEnabled(true);
    //    }
  });
}

CalcView::~CalcView() { delete ui; }

QLineEdit *CalcView::checkActiveLineEdit() {
  if (!ui->enterX->isChecked()) {
    //    std::cout << "RESHOW" << std::endl;
    return ui->resultShow;
  } else {
    //    std::cout << "EQUALX" << std::endl;
    return ui->equalX;
  }
}

void CalcView::focusInsert(QString add) {
  QPushButton *button = qobject_cast<QPushButton *>(sender());
  QLineEdit *activeLineEdit = checkActiveLineEdit();
  activeLineEdit->insert(button->text() + add);
  size_t currentlenPos;
  currentlenPos = button->text().length() + add.length();
  textLengthStack.push(currentlenPos);
}

void CalcView::equalClick() {
  QString equalResult = ui->resultShow->text();
  QString equalX = ui->equalX->text();
  emit uiEventEqual(equalResult, equalX);
  ui->resultShow->setText(equalResult);
}

void CalcView::ceClick() {
  if (!ui->resultShow->text().isEmpty()) {
    ui->resultShow->clear();
  }
}

void CalcView::acClick() {
  QLineEdit *activeLineEdit = checkActiveLineEdit();
  if (!activeLineEdit->text().isEmpty()) {
    activeLineEdit->selectionEnd();
    size_t textButtonLenght = 1;
    if (!textLengthStack.empty()) {
      textButtonLenght = textLengthStack.top();
      textLengthStack.pop();
    }
    while (textButtonLenght--) {
      if (!activeLineEdit->text().isEmpty()) activeLineEdit->backspace();
    }
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
  QString equalResult = ui->resultShow->text();
  emit sendData(equalResult);
}
