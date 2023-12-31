#include "graph.h"

Graph::Graph(QWidget *parent) : QWidget(parent), ui(new Ui::Graph) {
  ui->setupUi(this);

  connect(ui->update, &QPushButton::clicked, this, &Graph::graphClicked);
}
Graph::~Graph() { delete ui; }

void Graph::graphClicked() {
  int h = ui->caseBox->value() * 300;
  double xStart = ui->doubleSpinBox_xStart->value(),
         xEnd = ui->doubleSpinBox_xEnd->value(), yStart = 0, yEnd = 0;
  QVector<double> x(h + 1), y(h + 1);
  QString graphResult = ui->expression->text();

  emit uiEventOutputGraph(graphResult, x, y);
  emit uiEventResizeGraph(y, yStart, yEnd);
  emit uiEventResizeGraph(x, xStart, xEnd);
  // clear graphs
  ui->widget->clearGraphs();
  // create Graph and assign data to it:
  ui->widget->addGraph();
  ui->widget->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom);
  // create style
  QCPScatterStyle scatterStyle;
  scatterStyle.setShape(QCPScatterStyle::ssDisc); // Задаем форму точки, например, круг
  scatterStyle.setPen(QPen(Qt::black)); // Задаем цвет контура точки
  scatterStyle.setBrush(Qt::black); // Задаем цвет заполнения точки
  scatterStyle.setSize(2);
  // set only dots without line
  ui->widget->graph(0)->setLineStyle(QCPGraph::lsNone);
  ui->widget->graph(0)->setScatterStyle(scatterStyle);

  ui->widget->graph(0)->setData(x, y);

  // give the axes some labels:
  ui->widget->xAxis->setLabel("x");
  ui->widget->yAxis->setLabel("y");
  // set axes ranges, so we see all data:
  ui->widget->xAxis->setRange(xStart, xEnd);
  ui->widget->yAxis->setRange(yStart, yEnd);
  ui->widget->replot();
}

void Graph::sendResult(QString equalResult) {
  ui->expression->setText(equalResult);
  if (!this->isVisible()) {
    this->show();
  }
  emit uiEventSendUi(ui);
  this->graphClicked();
}
