#include "graph.h"

#include <QDebug>

#include "ui_graph.h"

Graph::Graph(QWidget *parent) : QWidget(parent), ui(new Ui::Graph) {
  ui->setupUi(this);
}
Graph::~Graph() { delete ui; }

void Graph::graphClicked() {
  int h = ui->caseBox->value() * 300;
  double xStart = ui->doubleSpinBox_xStart->value(),
         xEnd = ui->doubleSpinBox_xEnd->value();
  QVector<double> x(h + 1), y(h + 1);
  //  xStart = *std::min_element(x.constBegin(), x.constEnd());
  //  xEnd = *std::max_element(x.constBegin(), x.constEnd());
  //  double yStart = *std::min_element(y.constBegin(), y.constEnd()), yEnd =
  //  *std::max_element(y.constBegin(), y.constEnd());;
  double yStart = 0, yEnd = 0;
  QString graphResult = ui->expression->text();
//  try {
//    if (!graphResult.isEmpty()) {
      emit uiEventGraph(h, xStart, yStart, xEnd, yEnd, graphResult, x, y);
      // create Graph and assign data to it:
      ui->widget->addGraph();
      ui->widget->graph(0)->setData(x, y);
      // give the axes some labels:
      ui->widget->xAxis->setLabel("x");
      ui->widget->yAxis->setLabel("y");
      // set axes ranges, so we see all data:
      ui->widget->xAxis->setRange(xStart, xEnd);
      ui->widget->yAxis->setRange(yStart, yEnd);
      ui->widget->replot();
//    } else {
//      ui->expression->clear();
//    }
//  } catch (std::exception &e) {
//    QMessageBox::warning(this, "Warning!", QString::fromStdString(e.what()));
//  }
}

  void Graph::uiEventSendResult(QString equalResult) {
    ui->expression->setText(equalResult);
    if (!this->isVisible()) {
      this->show();
      this->graphClicked();
    } else {
      this->graphClicked();
    }
  }
