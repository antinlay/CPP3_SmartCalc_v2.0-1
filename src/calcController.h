#ifndef CALCCONTROLLER_H
#define CALCCONTROLLER_H

#include "calcModel.h"

class CalcController {
 private:
  CalcModel *model;

 public:
  CalcController(CalcModel *m) : model(m){};
  double add(double a);
  double sub(double a);
  double mult(double a);
  double div(double a);
  void reset();
};
#endif