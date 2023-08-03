#include <gtest/gtest.h>
#include <qmath.h>

#include "calcModel.h"
#include "qcustomplot.h"

namespace s21 {
class CalcTests : public testing::Test {
 protected:
  void calculate(QString& expr) { calc_.calculate(expr); }
  CalcModel calc_;
  QString err_div_zero_ = "1/0";
  QString err_sqrt_oppos_ = "sqrt(-1)";
  QString err_abracadabra_ = "1234g43s;;";
  QString err_empty_ = "";
  QString fail_expr_ = "1x";
  QString fail_lexem_ = "1;02941257";
  QString fail_x_lexem_ = "qwerty";
  QString fail_x_lexem_expr_ = "sin(x)";
  QString simple_log_ = "log(4)";
  QString simple_log_res_ = "0.60205999";
  QString multifold_ =
      "15/(7-(1+1))*3-(2+(1+1))*15/(7-(200+1))*3-(2+(1+1))*(15/"
      "(7-(1+1))*3-(2+(1+1))+15/(7-(1+1))*3-(2+(1+1)))";
  QString multifold_res_ = "-30.07216495";
  QString functions_t_ =
      "sin(1)+cos(1)+asin(1)+acos(1)+atan(1)+tan(1)+sqrt(16)+ln(10)+log(10)";
  QString functions_res_ = "12.5979606";
  QString folded_funcs_ = "(132+sin(asin(sqrt(ln(log(228.11)))))-4*5^6*(123))";
  QString folded_funcs_res_ = "-7687367.07378458";
  QString exp_notation_ = "2.5 * 10^3 + 1.8 * 10^-2 * (3.7e-5 + 2.1e2)";
  QString exp_notation_res_ = "2503.78000067";
  QString exp_not_simple_ = "1.5e5";
  QString exp_not_simple_res_ = "150000";
  QString degree_hard_ = "2^3^4";
  QString degree_hard_res_ = "2417851639229258349412352";
  QString degree_funcs = "sin(.2)^(cos(1)+tan(1.1))^sin(.6)";
  QString degree_funcs_res = "0.06624972";
  QString x_str_main_ =
      "sqrt((7.2 + 3.5 - 2.8) / (5.6 * 4.2)) + sin(x) - cos(1.3)";
  QString x_str_ = "0.8";
  double x_str_d_ = 0.8;
  QString x_str_res_ = "1.02941257";
  QString mod_ =
      "((sin(2.3) * (sqrt(7.8) + cos(1.2))) mod 4.5) / (log(5.6) + atan(0.9))";
  QString mod_res_ = "1.588689";
  QString graph_func_ = "x^2";
  double x_begin_ = -30;
  double y_begin_ = -30;
  double x_end_ = 30;
  double y_end_ = 900;
  QPair<QVector<double>, QVector<double>> vector_;
  QVector<double> XVector, YVector;
}
}  // namespace s21

TEST_F(MainCalc, DivByZero) {
  calculate(err_div_zero_);
  EXPECT_EQ(calc_.getResult(), error_);
}

int main(int argc, char* argv[]) {
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}