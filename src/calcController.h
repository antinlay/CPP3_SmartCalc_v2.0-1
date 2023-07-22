#ifndef CALCCONTROLLER_H
#define CALCCONTROLLER_H

#include <QMainWindow>

#include "calcModel.h"

namespace s21 {

class CalcController {
 public:
  void calcExpression(QString& equalResult, QString& equalX);
  bool validateChangeOn(QString equalStr);
  double calcGraph(QString graphResult, double x);

 private:
  s21::CalcModel resultModel;
};
}  // namespace s21
#endif  // CALCCONTROLLER_H
