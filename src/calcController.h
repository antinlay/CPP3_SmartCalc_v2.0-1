#ifndef CALCCONTROLLER_H
#define CALCCONTROLLER_H

#include "calcModel.h"

class CalcController {
 private:
 public:
  void getExpression(QString calc);
  void fixInfix(std::string& infix);
};
#endif