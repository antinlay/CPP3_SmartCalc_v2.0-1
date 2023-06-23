#ifndef GRAPH_H
#define GRAPH_H

#include <QWidget>

namespace Ui {
class Graph;
}

class Graph : public QWidget {
  Q_OBJECT

 public:
  explicit Graph(QWidget *parent = nullptr);
  ~Graph();
  void getData(QString res);
  char *strConvert(QString res, double val);

 public slots:
  void on_pushButton_clicked();

 private:
  Ui::Graph *ui;
};

#endif  // GRAPH_H
