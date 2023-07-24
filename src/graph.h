#ifndef GRAPH_H
#define GRAPH_H

#include <QWidget>

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
  void on_pushButton_clicked();
  void getData(QString res);

 private:
  Ui::Graph *ui;
  //  s21::CalcController resultController;
};

// }  // namespace s21
#endif  // GRAPH_H
