#include "graph.h"

#include "ui_graph.h"

Graph::Graph(QWidget *parent) : QWidget(parent), ui(new Ui::Graph) {
  ui->setupUi(this);
}
Graph::~Graph() { delete ui; }

char *Graph::strConvert(QString res, double val) {
  QString copy, num;
  QByteArray str;
  char *result;

  copy.push_back(res);
  num = QString::number(val);
  str = copy.replace('X', '(' + num + ')').toLocal8Bit();
  // change dot to comma for LINUX
#ifdef linux
  result = str.replace('.', ',').data();
#else
  result = str.data();
#endif
  return result;
}

void Graph::on_pushButton_clicked() {
  int h = ui->spinBox->value() * 100;
  double xStart = ui->doubleSpinBox_xStart->value(),
         xEnd = ui->doubleSpinBox_xEnd->value(), j = (xEnd - xStart) / h;
  QVector<double> x(h + 1), y(h + 1);
  QString res = ui->lineEdit_func->text();
  // calculate and write all graphics poins
  for (int i = 0; i <= h; ++i) {
    x[i] = xStart + i * j;
    // char *tmp = strConvert(res, x[i]);
    // y[i] = calculate(tmp);
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
