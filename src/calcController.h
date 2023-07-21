#ifndef CALCCONTROLLER_H
#define CALCCONTROLLER_H

#include "calcModel.h"

namespace s21 {

class CalcController {
 public:
  void getExpression(std::string& str);
  void fixInfix(std::string& infix);

 private:
  s21::CalcModel resultModel;
};
}  // namespace s21
#endif  // CALCCONTROLLER_H