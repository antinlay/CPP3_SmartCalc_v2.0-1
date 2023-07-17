#ifndef CALCCONTROLLER_H
#define CALCCONTROLLER_H

#include "calcModel.h"

class CalcController {
 public:
  void getExpression(std::string& str) {
    if (str.find("X") != std::string::npos) {
      int i = calc.length() - calc.indexOf("=") - 1;
      num = calc.right(i);
      calc = calc.left(calc.indexOf("=") - 2);
      if (calc.contains('X')) {
        calc = calc.replace('X', num);
      } else {
        ui->resultShow->setText("ERROR");
        return;
      }
    }
    std::string str = calc.toStdString();
    double result = 0;

    // if (validAriphSymb(str)) {
    result = resultModel.calculate(str);
    QString resCalc = QString::number(result, 'g', 14);
#ifdef linux
    resCalc.replace('.', ',');
#endif
    ui->resultShow->setText(resCalc);
  }
  // else {
  //   ui->resultShow->setText("ERROR");
  // }
  // }
};
void fixInfix(std::string& infix);

private:
s21::CalcModel resultModel;
}
;
#endif