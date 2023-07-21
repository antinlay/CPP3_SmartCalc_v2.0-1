#ifndef GRAPH_H
#define GRAPH_H

#include <QWidget>

#include "calcController.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class Graph;
}
QT_END_NAMESPACE
// namespace s21 {
class Graph : public QWidget {
  Q_OBJECT

 public:
  explicit Graph(QWidget *parent = nullptr);
  ~Graph();
  void getData(QString res);
  void strConvert(QString& res, double val);

 public slots:
  void on_pushButton_clicked();

 private:
  Ui::Graph *ui;
  s21::CalcController resultController;
};

// }  // namespace s21
#endif  // GRAPH_H
