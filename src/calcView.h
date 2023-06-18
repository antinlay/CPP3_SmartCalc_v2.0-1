#ifndef CalcVIEW_H
#define CalcVIEW_H

#include "calcController.h"

enum Choice {
  SUM = 1,
  SUB = 2,
  MUL = 3,
  DIV = 4,
  RES = 5,
  EXIT = 0,
  NONE = -1
};

class CalcView {
 private:
  CalcController *controller;

 public:
  CalcView(CalcController *c) : controller(c){};
  void displayMenu();
  int performChoice();
  double performNumericInput();
  void startEventLoop();
};

#endif