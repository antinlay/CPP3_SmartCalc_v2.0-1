#ifndef GRAPH_H
#define GRAPH_H

#include <QWidget>

namespace s21 {
class graph;
}

class graph : public QWidget {
  Q_OBJECT

 public:
  explicit graph(QWidget *parent = nullptr);
  ~graph();
  void getData(QString res);

 public slots:
  void on_pushButton_clicked();

 private:
  s21::graph *ui;
};

#endif  // GRAPH_H
