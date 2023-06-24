#ifndef GRAPH_H
#define GRAPH_H

#include <QWidget>

#include "calcModel.h"

//namespace s21 {
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
  void getData(QString res);
  std::string strConvert(QString res, double val);

 public slots:
  void on_pushButton_clicked();

 private:
  Ui::Graph *ui;
  s21::CalcModel resultModel;
};

//}  // namespace s21
#endif  // GRAPH_H
