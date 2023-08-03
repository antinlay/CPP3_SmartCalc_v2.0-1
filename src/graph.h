#ifndef GRAPH_H
#define GRAPH_H

#include "ui_graph.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class Graph;
}
QT_END_NAMESPACE

class Graph : public QWidget {
  Q_OBJECT

 public:
  explicit Graph(QWidget *parent = nullptr);
  ~Graph();

signals:
 void uiEventOutputGraph(QString& graphResult, QVector<double>& x,
                   QVector<double>& y);
 void uiEventResizeGraph(QVector<double>& y, double& yStart, double& yEnd);
 void uiEventSendUi(Ui::Graph* g);

 public slots:
  void graphClicked();
  void sendResult(QString equalResult);

 private:
  Ui::Graph *ui;
};

#endif  // GRAPH_H
