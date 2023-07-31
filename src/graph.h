#ifndef GRAPH_H
#define GRAPH_H

#include <QWidget>
#include <QtAlgorithms>

QT_BEGIN_NAMESPACE
namespace Ui {
class Graph;
}
QT_END_NAMESPACE
// namespace s21 {
class Graph : public QWidget {
  Q_OBJECT

 signals:
  void uiEventGraph(int& h, double& xStart, double& yStart, double& xEnd, double& yEnd, QString graphResult, QVector<double>& x, QVector<double>& y);

 public:
  explicit Graph(QWidget *parent = nullptr);
  ~Graph();

 public slots:
  void graphClicked();
  void uiEventSendResult(QString equalResult);

 private:
  Ui::Graph *ui;
};

// }  // namespace s21
#endif  // GRAPH_H
