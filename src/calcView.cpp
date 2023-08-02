#include "calcView.h"

CalcView::CalcView(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::CalcView) {
  ui->setupUi(this);

  ui->resultShow->setFocus();

  connect(ui->resultShow, &QLineEdit::editingFinished, this,
          [=]() { ui->equalX->clearFocus(); });

  connect(ui->equalX, &QLineEdit::editingFinished, this,
          [=]() { ui->resultShow->clearFocus(); });

  connect(qApp, &QApplication::focusChanged, this,
          &CalcView::onLineEditFocusChanged);

//  connect(ui->radioButton, &QRadioButton::clicked, this, &CalcView::degreeModeClicked);

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

  connect(ui->credit, &QPushButton::clicked, this, &CalcView::creditClicked);
  connect(ui->debit, &QPushButton::clicked, this, &CalcView::debitClicked);

  connect(ui->graph, &QPushButton::clicked, this, [=]() { graphClicked(); });

  connect(ui->equalX, &QLineEdit::textChanged, this, [=]() {
    if (ui->equalX->text().contains("X", Qt::CaseInsensitive)) {
      ui->equal->setEnabled(false);
    } else {
      ui->equal->setEnabled(true);
    }
  });
  connect(ui->resultShow, &QLineEdit::textChanged, this, [=]() {
    ui->progressBar->setValue(ui->resultShow->text().length());
    if (ui->resultShow->text().contains("X", Qt::CaseInsensitive)) {
      ui->equalX->setStyleSheet("border: 1px solid pink;");
      ui->graph->setEnabled(true);
    } else {
      ui->equalX->setStyleSheet("");
      ui->graph->setEnabled(false);
    }
    emit validateChangedOn(ui->resultShow->text(), status_);
    if (!status_) {
      ui->resultShow->setStyleSheet("border: 1px solid pink;");
      ui->equal->setEnabled(false);
    } else {
      ui->resultShow->setStyleSheet("");
      ui->equal->setEnabled(true);
      equalClick();
    }
  });
}

CalcView::~CalcView() { delete ui; }

QLineEdit *CalcView::checkActiveLineEdit() {
  if (ui->resultShow->isActiveWindow()) {
    ui->resultShow->setCursorPosition(ui->resultShow->text().length());
    ui->equalX->setStyleSheet("");
    ui->resultShow->setEnabled(true);
    ui->resultShow->setStyleSheet("border: 1px solid white;");
    return ui->resultShow;
  } else if (ui->equalX->isActiveWindow()) {
    ui->equalX->setCursorPosition(ui->resultShow->text().length());
    ui->equalX->setEnabled(true);
    ui->resultShow->setStyleSheet("");
    ui->equalX->setStyleSheet("border: 1px solid white;");
    return ui->equalX;
  }
  return ui->resultShow;
}

void CalcView::onLineEditFocusChanged(QWidget *newWidget) {
  QLineEdit *lineEdit = qobject_cast<QLineEdit *>(newWidget);
  if (lineEdit) {
    setLineEdit(lineEdit);
  }
}

void CalcView::focusInsert(QString add) {
  QPushButton *button = qobject_cast<QPushButton *>(sender());
  if (!lastActiveLineEdit_) lastActiveLineEdit_ = ui->resultShow;
  lastActiveLineEdit_->insert(button->text() + add);
  size_t currentlenPos;
  currentlenPos = button->text().length() + add.length();
  textLengthStack.push(currentlenPos);
}

void CalcView::equalClick() {
  QString equalResult = ui->resultShow->text();
  QString equalX = ui->equalX->text();
  try {
    if (!equalResult.isEmpty()) {
      emit uiEventSendUi(ui);
      emit uiEventEqual(equalResult, equalX);
      ui->result->setText(equalResult);
    } else {
      ui->result->clear();
    }
  } catch (std::exception &e) {
    QMessageBox::warning(this, "Warning!", QString::fromStdString(e.what()));
  }
}

void CalcView::ceClick() {
  if (!lastActiveLineEdit_->text().isEmpty()) {
    lastActiveLineEdit_->clear();
  }
}

void CalcView::acClick() {
  if (!lastActiveLineEdit_->text().isEmpty()) {
    lastActiveLineEdit_->selectionEnd();
    size_t textButtonLenght = 1;
    if (!textLengthStack.empty()) {
      textButtonLenght = textLengthStack.top();
      textLengthStack.pop();
    }
    while (textButtonLenght--) {
      if (!lastActiveLineEdit_->text().isEmpty())
        lastActiveLineEdit_->backspace();
    }
  }
}

void CalcView::creditClicked() { emit uiEventShowCredit(); }

void CalcView::debitClicked() { emit uiEventShowDebit(); }

void CalcView::graphClicked() {
  QString equalResult = ui->resultShow->text(), equalX = ui->equalX->text();
  emit uiEventReplaceX(equalResult, equalX);
  emit uiEventSendResult(equalResult);
}

//void CalcView::degreeModeClicked(bool checked) {
//  qDebug() << checked << "VIEW";
//  emit uiEventDegreeMode(checked);
//}
