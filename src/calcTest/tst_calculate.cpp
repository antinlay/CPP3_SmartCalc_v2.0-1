
#include <gmock/gmock-matchers.h>
#include <gtest/gtest.h>
#include "../calcModel.h"

using namespace s21;
class testModel : public testing::Test {\
public:
    QString resultCalc(double result) {
        return QString::number(result, 'f', 8);
    }
 protected:
  s21::CalcModel calc_;
  QString errDivZero = "1/0";
  QString errSqrtNegative = "sqrt(-1)";
  QString errAbracadabra = "1234g43s;;";
  QString errEmpty = "";
  QString failExpr = "1x";
  QString failLexem = "1;02941257";
  QString failLetter = "qwerty";
  QString failLetterX = "sin(x)";
  QString simpleLog = "log(4)";
  QString simpleLogRes = "0.60205999";
  QString multiFold = "15/(7-(1+1))*3-(2+(1+1))*15/(7-(200+1))*3-(2+(1+1))*(15/"
      "(7-(1+1))*3-(2+(1+1))+15/(7-(1+1))*3-(2+(1+1)))";
  QString multiFoldRes = "-30.07216495";
  QString funcExpr =
      "sin(1)+cos(1)+asin(1)+acos(1)+atan(1)+tan(1)+sqrt(16)+ln(10)+log(10)";
  QString funcExprRes = "12.59796060";
  QString foldedFuncs = "(132+sin(asin(sqrt(ln(log(228.11)))))-4*5^6*(123))";
  QString foldedFuncsRes = "-7687367.07378458";
  QString expNotation = "2.5 * 10^3 + 1.8 * 10^-2 * (3.7e-5 + 2.1e2)";
  QString expNotationRes = "2503.78000067";
  QString expEasy = "1.5e5";
  QString expEasyRes = "150000";
  QString powTwo = "2^3^4";
  QString powTwoRes = "2417851639229258349412352";
  QString powFuncs = "sin(.2)^(cos(1)+tan(1.1))^sin(.6)";
  QString powFuncsRes = "0.06624972";
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
  std::pair<std::vector<double>, std::vector<double>> vector_;
  std::vector<double> XVector, YVector;
};

TEST_F(testModel, errors) {
  EXPECT_THROW(calc_.calculate(errDivZero), std::runtime_error);
  EXPECT_THROW(calc_.calculate(errSqrtNegative), std::runtime_error);
  EXPECT_THROW(calc_.calculate(errAbracadabra), std::invalid_argument);
  EXPECT_THROW(calc_.calculate(errEmpty), std::invalid_argument);
}

TEST_F(testModel, equals) {
    qDebug() << resultCalc(calc_.calculate(simpleLog));
    EXPECT_EQ(resultCalc(calc_.calculate(simpleLog)), simpleLogRes);
    qDebug() << resultCalc(calc_.calculate(multiFold));
    EXPECT_EQ(resultCalc(calc_.calculate(multiFold)), multiFoldRes);
    qDebug() << resultCalc(calc_.calculate(funcExpr));
    EXPECT_EQ(resultCalc(calc_.calculate(funcExpr)), funcExprRes);
    qDebug() << resultCalc(calc_.calculate(foldedFuncs));
    EXPECT_EQ(resultCalc(calc_.calculate(foldedFuncs)), foldedFuncsRes);
    qDebug() << resultCalc(calc_.calculate(expNotation));
    EXPECT_EQ(resultCalc(calc_.calculate(expNotation)), expNotationRes);
}
