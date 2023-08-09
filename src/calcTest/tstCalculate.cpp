#include <gmock/gmock-matchers.h>
#include <gtest/gtest.h>

#include "../calcModel.h"

using namespace s21;
class testModel : public testing::Test {
 protected:
  // Equal
  s21::CalcModel calc_;
  QString errDivZero = "1/0";
  QString errModZero = "11mod(0)";
  QString errSqrtNegative = "sqrt(-1)";
  QString errAbracadabra = "1234g43s;;";
  QString errEmpty = "";
  QString failExpr = "1x";
  QString failLexem = "1;02941257";
  QString failLetter = "qwerty";
  QString failLetterX = "sin(x)";
  QString replaceRes = "0.01050774";
  QString simpleLog = "log(4)";
  QString simpleLogRes = "0.60205999";
  QString multiFold =
      "15/(7-(1+1))*3-(2+(1+1))*15/(7-(200+1))*3-(2+(1+1))*(15/"
      "(7-(1+1))*3-(2+(1+1))+15/(7-(1+1))*3-(2+(1+1)))";
  QString multiFoldRes = "-30.07216495";
  QString funcExpr =
      "sin(1)+cos(1)+asin(1)+acos(1)+atan(1)+tan(1)+sqrt(16)+ln(10)+log(10)";
  QString funcExprRes = "12.5979606";
  QString foldedFuncs = "(132+sin(asin(sqrt(ln(log(228.11)))))-4*5^6*(123))";
  QString foldedFuncsRes = "-7687367.07378458";
  QString expNotation = "2.5*10^3+1.8*10^-2*(3.7e-5+2.1e2)";
  QString expNotationRes = "2503.78000067";
  QString expEasy = "1.5e5";
  QString expEasyRes = "150000";
  QString powTwo = "2^3^4";
  QString powTwoRes = "2417851639229258349412352";
  QString powFuncs = "sin(.2)^(cos(1)+tan(1.1))^sin(.6)";
  QString powFuncsRes = "0.06624972";
  QString mod = "((sin(2.3)*(sqrt(7.8)+cos(1.2)))mod4.5)/(log(5.6)+atan(0.9))";
  QString modRes = "1.588689";
  // Graph
  int h = 5;
  QVector<double> xDots, yDots;
  QString xRes = "-8.53333333", yRes = "-0.14838471";
  // Credit Debit
  QString
      info = "",
      payment = "", overpayment = "", deposit = "", profit = "",
      difInfo =
          "Pay for August 2023: 34416.67 interest amount: 1083.33\nPay for "
          "August 2023: 34055.56 interest amount: 722.22\nPay for August 2023: "
          "33694.44 interest amount: 361.11\n",
      anuInfo =
          "Pay for August 2023: 34416.67 interest amount: 1083.33\nPay for "
          "August 2023: 34055.56 interest amount: 722.22\nPay for August 2023: "
          "33694.44 interest amount: 361.11\nPay for August 2023: 50563.20 "
          "overpayment: 563.20\nPay for August 2023: 50563.20 overpayment: "
          "563.20\n",
      anuPay = "101126.40", anuOverpay = "1126.40", difPay = "102166.67",
      difOverpay = "2166.67",
      depInfo =
          "Total for 9 September 2023: 101065.57 profit: 1065.57\nTotal for 9 "
          "October 2023: 102178.40 profit: 1112.83\nTotal for 9 November 2023: "
          "103267.19 profit: 1088.79\nTotal for 9 December 2023: 104404.25 "
          "profit: 1137.07\nTotal for 9 January 2024: 106295.51 profit: "
          "1891.26\n",
      depRes = "106295.51", profitRes = "6295.51";
  QDate currentDate = QDate::fromString("09/08/2023", "dd/MM/yyyy");
  QDate depositDate = QDate::fromString("16/08/2023", "dd/MM/yyyy");
  QDate endDate = QDate::fromString("31/12/2023", "dd/MM/yyyy");
};

TEST_F(testModel, errors) {
  EXPECT_THROW(calc_.calculate(errDivZero), std::runtime_error);
  EXPECT_THROW(calc_.calculate(errModZero), std::runtime_error);
  EXPECT_THROW(calc_.calculate(errSqrtNegative), std::runtime_error);
  EXPECT_THROW(calc_.calculate(errAbracadabra), std::invalid_argument);
  EXPECT_THROW(calc_.calculate(errEmpty), std::invalid_argument);
}

TEST_F(testModel, equals) {
  EXPECT_EQ(calc_.humanResult(calc_.calculate(simpleLog)), simpleLogRes);
  EXPECT_EQ(calc_.humanResult(calc_.calculate(multiFold)), multiFoldRes);
  EXPECT_EQ(calc_.humanResult(calc_.calculate(funcExpr)), funcExprRes);
  EXPECT_EQ(calc_.humanResult(calc_.calculate(foldedFuncs)), foldedFuncsRes);
  EXPECT_EQ(calc_.humanResult(calc_.calculate(expNotation)), expNotationRes);
  EXPECT_EQ(calc_.humanResult(calc_.calculate(expEasy)), expEasyRes);
  EXPECT_EQ(calc_.humanResult(calc_.calculate(powTwo)), powTwoRes);
  EXPECT_EQ(calc_.humanResult(calc_.calculate(powFuncs)), powFuncsRes);
  EXPECT_EQ(calc_.humanResult(calc_.calculate(mod)), modRes);
}

TEST_F(testModel, graph) {
  xDots.reserve(1501);
  yDots.reserve(1501);
  calc_.setGraphStructureValues(h, -10, 10);
  calc_.outputGraph(failLetterX, xDots, yDots);
  qDebug() << calc_.humanResult(xDots[110]) << " "
           << calc_.humanResult(yDots[110]);
  EXPECT_EQ(calc_.humanResult(xDots[110]), xRes);
  EXPECT_EQ(calc_.humanResult(yDots[110]), yRes);
}

TEST_F(testModel, credit) {
  calc_.setCreditStructureValues(100000, 13, 1, currentDate, 3);
  calc_.outputCredit(info, payment, overpayment);
  EXPECT_EQ(info, difInfo);
  EXPECT_EQ(payment, difPay);
  EXPECT_EQ(overpayment, difOverpay);
  calc_.setCreditStructureValues(100000, 9, 0, currentDate, 2);
  calc_.outputCredit(info, payment, overpayment);
  EXPECT_EQ(info, anuInfo);
  EXPECT_EQ(payment, anuPay);
  EXPECT_EQ(overpayment, anuOverpay);
}

TEST_F(testModel, debit) {
  info.clear();
  calc_.setDepStructureValues(100000, 13, 1, true, currentDate, endDate);
  calc_.setReDepStructureValues("1123", depositDate, 1);
  calc_.setWithdrawStructureValues("999", depositDate, 1);
  calc_.outputDebit(info, deposit, profit);
  EXPECT_EQ(info, depInfo);
  EXPECT_EQ(deposit, depRes);
  EXPECT_EQ(profit, profitRes);
}

TEST_F(testModel, replaceX) {
  calc_.setUseDegree(true);
  calc_.replaceX(failLetterX, simpleLogRes);
  EXPECT_EQ(calc_.humanResult(calc_.calculate(failLetterX)), replaceRes);
}
