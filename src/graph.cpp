#include "graph.h"

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
  QString res = ui->lineEdit_func->text();
  // s21::CalcModel::calculate and write all graphics points
  for (int i = 0; i <= h; ++i) {
    x[i] = xStart + i * j;
//    y[i] = resultController.calcGraph(res, x[i]);
  }

  // find max and min in elements
  double yStart = *std::min_element(y.begin(), y.end());
  double yEnd = *std::max_element(y.begin(), y.end());
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

void Graph::getData(QString res) { ui->lineEdit_func->setText(res); }
