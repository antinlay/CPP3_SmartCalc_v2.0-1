#include "graph.h"

#include <QDebug>
#include <QVector>

#include "ui_graph.h"

Graph::Graph(QWidget *parent) : QWidget(parent), ui(new Ui::Graph) {
  ui->setupUi(this);

  connect(ui->update, &QPushButton::clicked, this,  &Graph::graphClicked);
}
Graph::~Graph() { delete ui; }

void Graph::graphClicked() {
  int h = ui->caseBox->value() * 300;
  double xStart = ui->doubleSpinBox_xStart->value(),
         xEnd = ui->doubleSpinBox_xEnd->value();
  QVector<double> x(h + 1), y(h + 1);

  double yStart = 0, yEnd = 0;
  QString graphResult = ui->expression->text();

  emit uiEventGraph(h, xStart, yStart, xEnd, yEnd, graphResult, x, y);

  qDebug() << "x: " << xStart << " " << xEnd << "y: " << yStart << yEnd;

  ui->widget->clearGraphs();
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
