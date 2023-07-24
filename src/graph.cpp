#include "graph.h"
#include <QDebug>
#include "ui_graph.h"

Graph::Graph(QWidget *parent) : QWidget(parent), ui(new Ui::Graph) {
  ui->setupUi(this);
}
Graph::~Graph() { delete ui; }

void Graph::on_pushButton_clicked() {
  int h = ui->spinBox->value() * 300;
  double xStart = ui->doubleSpinBox_xStart->value(),
         xEnd = ui->doubleSpinBox_xEnd->value(), j = (xEnd - xStart) / h;
  QVector<double> x(h + 1), y(h + 1);
  QString graphResult = ui->lineEdit_func->text();
  double yStart = -10, yEnd = 10;
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
}

void Graph::getData(QString res) {
  ui->lineEdit_func->setText(res);
  if (!this->isVisible()) {
      this->show();
      this->on_pushButton_clicked();
  } else {
      this->on_pushButton_clicked();
  }
}
