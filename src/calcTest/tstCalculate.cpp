#include <gmock/gmock-matchers.h>
#include <gtest/gtest.h>

#include "../calcModel.h"

class testModel : public testing::Test {
 protected:
  // Equal
  double result = 0;
  s21::CalcModel calc_;
  QString errDivZero = "1/0";
  QString errModZero = "11mod(0)";
  QString errSqrtNegative = "sqrt(-1)";
  QString errAbracadabra = "1234g43s;;";
  QString errEmpty = "";
  QString failExpr = "1x";
  QString failLexem = "1;02941257";
  QString failLetter = "qwerty";
  QString failLetterX = "sqrt(x)";
  QString replaceRes = "0.77592525";
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
  double xStart = -10, xEnd = 10;
  QVector<double> xDots{}, yDots{};
  QString xRes = "4.66666667", yRes = "2.16024767";
  // Credit Debit
  QString
      info = "",
      payment = "", overpayment = "", deposit = "", profit = "",
      difInfo =
          "Pay for November 2023: 34416.67 interest amount: 1083.33\nPay for "
          "November 2023: 34055.56 interest amount: 722.22\nPay for November "
          "2023: 33694.44 interest amount: 361.11\n",
      anuInfo =
          "Pay for November 2023: 50563.20 overpayment: 563.20\nPay for "
          "November 2023: 50563.20 overpayment: 563.20\n",
      anuPay = "101126.40", anuOverpay = "1126.40", difPay = "102166.67",
      difOverpay = "2166.67",
      depInfo =
          "Total for 9 December 2023: 101101.09 profit: 1101.09\nDeposite for "
          "31 December 2023: 102224.09 amount: 1123.00\nTotal for 9 January "
          "2024: 104075.86 profit: 1851.76\nDeposite for 31 January 2024: "
          "105198.86 amount: 1123.00\nWithdraw for 29 February 2024: 104199.86 "
          "amount: 999.00\nTotal for 29 February 2024: 105273.17 profit: "
          "1073.32\nDeposite for 29 February 2024: 106396.17 amount: "
          "1123.00\nWithdraw for 29 March 2024: 105397.17 amount: "
          "999.00\nTotal for 29 March 2024: 106557.69 profit: "
          "1160.52\nDeposite for 29 March 2024: 107680.69 amount: "
          "1123.00\nTotal for 29 April 2024: 108828.11 profit: 1147.42\n",
      depRes = "108828.11", profitRes = "6334.11",
      depWeekInfo =
          "Total for 16 November 2023: 100248.63 profit: 248.63\nTotal for 23 "
          "November 2023: 100497.89 profit: 249.25\nTotal for 30 November "
          "2023: 100747.76 profit: 249.87\nTotal for 7 December 2023: "
          "100998.25 profit: 250.49\nTotal for 14 December 2023: 101249.37 "
          "profit: 251.12\nTotal for 21 December 2023: 101501.11 profit: "
          "251.74\nTotal for 28 December 2023: 101753.47 profit: 252.37\nTotal "
          "for 4 January 2024: 102006.47 profit: 252.99\nTotal for 11 January "
          "2024: 102260.09 profit: 253.62\nTotal for 18 January 2024: "
          "102514.34 profit: 254.25\nTotal for 25 January 2024: 102769.23 "
          "profit: 254.89\nTotal for 1 February 2024: 103024.75 profit: "
          "255.52\nTotal for 8 February 2024: 103280.90 profit: 256.15\nTotal "
          "for 15 February 2024: 103537.69 profit: 256.79\nTotal for 22 "
          "February 2024: 103795.12 profit: 257.43\nTotal for 29 February "
          "2024: 104053.19 profit: 258.07\nTotal for 7 March 2024: 104311.90 "
          "profit: 258.71\nTotal for 14 March 2024: 104571.26 profit: "
          "259.35\nTotal for 21 March 2024: 104831.26 profit: 260.00\nTotal "
          "for 28 March 2024: 105091.90 profit: 260.65\nTotal for 30 March "
          "2024: 105166.56 profit: 74.66\n",
      depWeekRes = "105166.56", profitWeekRes = "5166.56", reDep = "1123",
      withdraw = "999";
  QDate currentDate = QDate::fromString("09/11/2023", "dd/MM/yyyy"),
        depositDate = QDate::fromString("31/12/2023", "dd/MM/yyyy"),
        endDate = QDate::fromString("30/03/2024", "dd/MM/yyyy");
};

TEST_F(testModel, simpleLog) {
  result = calc_.calculate(simpleLog);
  EXPECT_EQ(calc_.humanResult(result), simpleLogRes);
}
TEST_F(testModel, multiFold) {
  result = calc_.calculate(multiFold);
  EXPECT_EQ(calc_.humanResult(result), multiFoldRes);
}
TEST_F(testModel, funcExpr) {
  result = calc_.calculate(funcExpr);
  EXPECT_EQ(calc_.humanResult(result), funcExprRes);
}
TEST_F(testModel, foldedFuncs) {
  result = calc_.calculate(foldedFuncs);
  EXPECT_EQ(calc_.humanResult(result), foldedFuncsRes);
}
TEST_F(testModel, expNotation) {
  result = calc_.calculate(expNotation);
  EXPECT_EQ(calc_.humanResult(result), expNotationRes);
}
TEST_F(testModel, expEasy) {
  result = calc_.calculate(expEasy);
  EXPECT_EQ(calc_.humanResult(result), expEasyRes);
}
TEST_F(testModel, powTwo) {
  result = calc_.calculate(powTwo);
  EXPECT_EQ(calc_.humanResult(result), powTwoRes);
}
TEST_F(testModel, powFuncs) {
  calc_.setUseDegree(false);
  result = calc_.calculate(powFuncs);
  EXPECT_EQ(calc_.humanResult(result), powFuncsRes);
}
TEST_F(testModel, mod) {
  calc_.setUseDegree(false);
  result = calc_.calculate(mod);
  EXPECT_EQ(calc_.humanResult(result), modRes);
}

TEST_F(testModel, outputGraph) {
  xDots.reserve(1500);
  yDots.reserve(1500);
  calc_.setGraphStructureValues(h, xStart, xEnd);
  calc_.outputGraph(failLetterX, xDots, yDots);
  QString xDot = calc_.humanResult(xDots[1100]),
          yDot = calc_.humanResult(yDots[1100]);
  EXPECT_EQ(xDot, xRes);
  EXPECT_EQ(yDot, yRes);
}
TEST_F(testModel, resizeGraph) {
  xDots.reserve(1501);
  yDots.reserve(1501);
  calc_.setGraphStructureValues(h, xStart, xEnd);
  calc_.resizeGraph(xDots, xStart, xEnd);
  EXPECT_EQ(xStart, -10.0);
  EXPECT_EQ(xEnd, 10.0);
}

TEST_F(testModel, outputCreditDif) {
  calc_.setCreditStructureValues(100000, 13, 1, currentDate, 3);
  calc_.outputCredit(info, payment, overpayment);
  EXPECT_EQ(info, difInfo);
  EXPECT_EQ(payment, difPay);
  EXPECT_EQ(overpayment, difOverpay);
}

TEST_F(testModel, outputCreditAnu) {
  calc_.setCreditStructureValues(100000, 9, 0, currentDate, 2);
  calc_.outputCredit(info, payment, overpayment);
  EXPECT_EQ(info, anuInfo);
  EXPECT_EQ(payment, anuPay);
  EXPECT_EQ(overpayment, anuOverpay);
}

TEST_F(testModel, outputDebit) {
  calc_.setDepStructureValues(100000, 13, 1, true, currentDate, endDate);
  calc_.setReDepStructureValues(reDep, depositDate, 1);
  calc_.setWithdrawStructureValues(withdraw, depositDate, 0);
  calc_.outputDebit(info, deposit, profit);
  EXPECT_EQ(info, depInfo);
  EXPECT_EQ(deposit, depRes);
  EXPECT_EQ(profit, profitRes);
}
TEST_F(testModel, outputDebitWeek) {
  calc_.setDepStructureValues(100000, 13, 0, true, currentDate, endDate);
  calc_.outputDebit(info, deposit, profit);
  EXPECT_EQ(info, depWeekInfo);
  EXPECT_EQ(deposit, depWeekRes);
  EXPECT_EQ(profit, profitWeekRes);
}

TEST_F(testModel, replaceX) {
  calc_.setUseDegree(true);
  calc_.replaceX(failLetterX, simpleLogRes);
  EXPECT_EQ(calc_.humanResult(calc_.calculate(failLetterX)), replaceRes);
}

TEST_F(testModel, errors) {
  EXPECT_THROW(calc_.calculate(errDivZero), std::runtime_error);
  EXPECT_THROW(calc_.calculate(errModZero), std::runtime_error);
  EXPECT_THROW(calc_.calculate(errSqrtNegative), std::runtime_error);
  EXPECT_THROW(calc_.calculate(errAbracadabra), std::invalid_argument);
  EXPECT_THROW(calc_.calculate(errEmpty), std::invalid_argument);
}
