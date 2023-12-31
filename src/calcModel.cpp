#include "calcModel.h"

void s21::CalcModel::changeDegreesToRadians(double& a) {
  if (useDegree_) {
    a = a * (M_PI / 180.0);
  }
};

void s21::CalcModel::substituteExpr(QString& expression) {
  expression.remove(' ');
  expression.replace("log", "log10");
  expression.replace("ln", "log");
  expression.replace("mod", "%");
  expression.replace("e", "*10^");
}

bool s21::CalcModel::validateExpression(QString expression) {
  substituteExpr(expression);
  exprtk::symbol_table<double> symbol_table;
  exprtk::expression<double> expr;
  exprtk::parser<double> parser;
  symbol_table.add_constants();
  double x;
  symbol_table.add_variable("x", x);
  symbol_table.add_variable("X", x);
  expr.register_symbol_table(symbol_table);
  if (!parser.compile(expression.toStdString(), expr)) return false;
  return true;
}

double s21::CalcModel::addCalc(double a, double b) { return a + b; }
double s21::CalcModel::subtractCalc(double a, double b) { return a - b; }
double s21::CalcModel::multiplyCalc(double a, double b) { return a * b; }
double s21::CalcModel::divideCalc(double a, double b) {
  if (b == 0) {
    throw std::runtime_error("Undefined divide zero: " + std::to_string(a) +
                             " / " + std::to_string(b));
  }
  return a / b;
}

double s21::CalcModel::modCalc(double a, double b) {
  if (b == 0) {
    throw std::runtime_error("Undefined divide zero: " + std::to_string(a) +
                             " mod " + std::to_string(b));
  }
  return std::fmod(a, b);
}

double s21::CalcModel::powerCalc(double a, double b) { return qPow(a, b); }

double s21::CalcModel::sqrtCalc(double a) {
  if (a < 0) {
    throw std::runtime_error("Undefined square root of a negative number: " +
                             std::to_string(a));
  }

  return qSqrt(a);
}
// FUNCTIONS
double s21::CalcModel::lnCalc(double a) { return qLn(a); }
double s21::CalcModel::logCalc(double a) { return std::log10(a); }
double s21::CalcModel::tanCalc(double a) {
  changeDegreesToRadians(a);
  return qTan(a);
}
double s21::CalcModel::atanCalc(double a) {
  changeDegreesToRadians(a);
  return qAtan(a);
}
double s21::CalcModel::sinCalc(double a) {
  changeDegreesToRadians(a);
  return qSin(a);
}
double s21::CalcModel::asinCalc(double a) {
  changeDegreesToRadians(a);
  return qAsin(a);
}
double s21::CalcModel::cosCalc(double a) {
  changeDegreesToRadians(a);
  return qCos(a);
}
double s21::CalcModel::acosCalc(double a) {
  changeDegreesToRadians(a);
  return qAcos(a);
}

// CHECKS
int s21::CalcModel::getPriority(QString c) {
  int res = 0;
  if (isFunction(c)) {
    res = 4;
  } else {
    res = precedences_.value(c);
  }
  return res;
}

bool s21::CalcModel::isDigital(QChar& currentChar, QString& infix, int& i) {
  bool result =
      currentChar.isDigit() || currentChar == '.' || currentChar == 'e';

  if (currentChar == '-') {
    if (i == 0 || (!infix[i - 1].isDigit() && infix[i - 1] != ')')) {
      result = true;
    }
  }

  return result;
}

bool s21::CalcModel::isOperator(const QString& str) {
  bool result = false;
  if (!str.isEmpty()) {
    QString listOperators = "+-*/%^";
    if (listOperators.contains(str)) result = true;
  }
  return result;
}

bool s21::CalcModel::isFunction(const QString& str) {
  bool result = false;
  if (!str.isEmpty()) {
    QString listOperators = "qgaiontsc";
    if (listOperators.contains(str)) result = true;
  }
  return result;
}

// MAP CALCULATIONS
double s21::CalcModel::calcOperations(double a, double b, QString c) {
  typedef double (s21::CalcModel::*Operation)(double, double);
  QMap<QString, Operation> operations = {{"+", &s21::CalcModel::addCalc},
                                         {"-", &s21::CalcModel::subtractCalc},
                                         {"*", &s21::CalcModel::multiplyCalc},
                                         {"/", &s21::CalcModel::divideCalc},
                                         {"%", &s21::CalcModel::modCalc},
                                         {"^", &s21::CalcModel::powerCalc}};
  return (this->*operations.value(c))(a, b);
}

double s21::CalcModel::calcFunctions(double a, QString c) {
  typedef double (s21::CalcModel::*Function)(double);
  QMap<QString, Function> functions = {
      {"q", &s21::CalcModel::sqrtCalc}, {"n", &s21::CalcModel::lnCalc},
      {"g", &s21::CalcModel::logCalc},  {"t", &s21::CalcModel::tanCalc},
      {"a", &s21::CalcModel::atanCalc}, {"s", &s21::CalcModel::sinCalc},
      {"i", &s21::CalcModel::asinCalc}, {"c", &s21::CalcModel::cosCalc},
      {"o", &s21::CalcModel::acosCalc}};
  return (this->*functions.value(c))(a);
}

void s21::CalcModel::isEmptyBracket(QString& currentToken,
                                    QQueue<QString>& outputQueue) {
  if (!currentToken.isEmpty()) {
    outputQueue.push_back(currentToken);
    currentToken = "";
  }
}
void s21::CalcModel::isBrackets(QChar& currentChar,
                                QQueue<QString>& outputQueue,
                                QStack<QString>& operatorStack) {
  if (currentChar == '(') {
    operatorStack.push(QString(1, currentChar));
  } else if (currentChar == ')') {
    while (operatorStack.top() != "(") {
      outputQueue.push_back(operatorStack.top());
      operatorStack.pop();
    }
    operatorStack.pop();
  } else {
    while (!operatorStack.empty() && operatorStack.top() != "(" &&
           getPriority(QString(1, currentChar)) <=
               getPriority(operatorStack.top())) {
      // Right-associative power of degree
      if (currentChar == '^' && operatorStack.top() == "^") {
        break;
      }
      outputQueue.push_back(operatorStack.top());
      operatorStack.pop();
    }
    operatorStack.push(QString(1, currentChar));
  }
}

void s21::CalcModel::isEmptyToken(QString& currentToken,
                                  QQueue<QString>& outputQueue) {
  if (!currentToken.isEmpty()) {
    outputQueue.push_back(currentToken);
  }
}
void s21::CalcModel::isEmptyStack(QQueue<QString>& outputQueue,
                                  QStack<QString>& operatorStack) {
  while (!operatorStack.empty()) {
    outputQueue.push_back(operatorStack.top());
    operatorStack.pop();
  }
}

// CONVERT TO POSTFIX
QQueue<QString> s21::CalcModel::infixToPostfix(QString& infix) {
  QStack<QString> operatorStack;
  QQueue<QString> outputQueue;
  QString currentToken = "";
  // Main loop for chars
  for (int i = 0; i < infix.length(); i++) {
    QChar currentChar = infix[i];
    // Check is Digital or exponential
    if (isDigital(currentChar, infix, i)) {
      if (currentChar == 'e') {
        currentToken += currentChar;
        currentChar = infix[++i];
      }
      currentToken += currentChar;
      // Check is Letter
    } else if (QChar(currentChar).isLetter()) {
      QString function;
      while (QChar(currentChar).isLetter()) {
        function += currentChar;
        currentChar = infix[++i];
      }
      function = keyFunctions.value(function);
      operatorStack.push(function);
      --i;
    } else {
      // Check brackets
      isEmptyBracket(currentToken, outputQueue);
      isBrackets(currentChar, outputQueue, operatorStack);
    }
  }
  // Checks is empty
  isEmptyToken(currentToken, outputQueue);
  isEmptyStack(outputQueue, operatorStack);
  return outputQueue;
}

// CALCULATE POSTFIX
double s21::CalcModel::getFromStack(QStack<double>& operands) {
  double operand = 0;
  if (!operands.empty()) {
    operand = operands.top();
    operands.pop();
  }
  return operand;
}

double s21::CalcModel::calculatePostfix(QQueue<QString> postfix) {
  QStack<double> calcStack;
  QString token = "";
  while (!postfix.empty()) {
    token = postfix.front();
    postfix.pop_front();
    if (isOperator(token)) {
      double operand1 = getFromStack(calcStack);
      double operand2 = getFromStack(calcStack);
      double resultOperation = calcOperations(operand2, operand1, token);
      calcStack.push(resultOperation);
    } else if (isFunction(token)) {
      double topStack = getFromStack(calcStack);
      double resultFunc = calcFunctions(topStack, token);
      calcStack.push(resultFunc);
    } else {
      double result = token.toDouble();
      calcStack.push(result);
    }
  }
  return calcStack.top();
}

void s21::CalcModel::replaceX(QString& equalResult, QString& equalLabel) {
  if (equalResult.contains("X", Qt::CaseInsensitive) && !equalLabel.isEmpty()) {
    equalResult =
        equalResult.replace("X", "(" + equalLabel + ")", Qt::CaseInsensitive);
  }
}

double s21::CalcModel::calculate(QString infix) {
  QString expression = infix;
  if (!validateExpression(expression)) {
    throw std::invalid_argument("Input Error: " + expression.toStdString() +
                                " wrong expression");
    return 0.0;
  }
  QQueue<QString> newInfix = infixToPostfix(infix);
  return calculatePostfix(newInfix);
}

QString s21::CalcModel::humanResult(double result) {
  static QRegularExpression regExpr = QRegularExpression("[,.]?0+$");
  return QString::number(result, 'f', 8).remove(regExpr);
}

// CALCULATE CREDIT
void s21::CalcModel::paymentAnnuityCalc(double& p, double& P) {
  /* Кредитный калькулятор с аннуитетными платежами можно рассчитать по
   следующей формуле: p = (S * i * (1 + i)^n) / ((1 + i)^n - 1)? где: p -
   размер ежемесячного платежа, S - сумма кредита, i - процентная ставка в
   месяц,  n - количество месяцев, O - общая переплата, o - месячная
   переплата, P - обшая переплата */
  unsigned short n = CreditStruct.months;
  double S = CreditStruct.summ, i = CreditStruct.interestRate / 100 / 12;
  p = (S * (i * qPow((1 + i), n))) / (qPow((1 + i), n) - 1);
  P = p * n;
}

void s21::CalcModel::paymentDifferentialCalc(double& p, double& o, size_t m) {
  /* Формула для расчета дифференцированного платежа выглядит следующим
   образом : P = (S / n) + (S - (m - 1) * (S / n)) * i, где: P - размер
   дифференцированного платежа, S - сумма кредита, n - срок кредита в
   месяцах, m - номер текущего месяца, i - годовая процентная ставка,
   деленная на 12 месяцев. i = (S - (m - 1) * (S / n)) * i */
  double S = CreditStruct.summ, i = CreditStruct.interestRate / 100 / 12;
  size_t n = CreditStruct.months;
  p = (S / n) + (S - (m - 1) * (S / n)) * i;
  o = (S - (m - 1) * (S / n)) * i;
}

void s21::CalcModel::outputCredit(QString& anuInfo, QString& payment,
                                  QString& overpayment) {
  unsigned short m = 1;
  double o = 0, O = 0, p = 0, P = 0;
  QString rateOrPayment = " overpayment: ";
  QDate currentDate = CreditStruct.currentDate;

  if (CreditStruct.caseIndex == 0) {
    paymentAnnuityCalc(p, P);
    O = P - CreditStruct.summ;
    o = O / CreditStruct.months;
  }

  while (m <= CreditStruct.months) {
    QString currentYear = QString::number(CreditStruct.currentDate.year());
    QString currentMonth =
        QLocale().monthName(CreditStruct.currentDate.month());

    if (CreditStruct.caseIndex == 1) {
      rateOrPayment = " interest amount: ";
      paymentDifferentialCalc(p, o, m);
      P += p;
      O += o;
    }
    anuInfo += "Pay for " + currentMonth + " " + currentYear + ": " +
               QString::number(p, 'f', 2) + rateOrPayment +
               QString::number(o, 'f', 2) + "\n";

    currentDate = currentDate.addMonths(1);
    ++m;
  }
  // send values to controller from refference
  payment = QString::number(P, 'f', 2);
  overpayment = QString::number(O, 'f', 2);
}

// CALCULATE DEPOSIT
void s21::CalcModel::fixDate(QDate& fixDate, unsigned short startCurrentDay) {
  if (fixDate.month() == 2 || startCurrentDay == 31) {
    fixDate.setDate(fixDate.year(), fixDate.month(), fixDate.daysInMonth());
  }
}

void s21::CalcModel::reDepositWithdrawCalculate(QDate& currentDate,
                                                QDate& pasteDate,
                                                QDate& itterator,
                                                double& finalAmount,
                                                QString& anuInfo, bool flag) {
  QString summ = ReDepositStruct.summDep;
  int caseIndex = ReDepositStruct.caseIndexDep;
  pasteDate = ReDepositStruct.depositDate;
  if (flag) {
    summ = WithdrawStruct.summWithdraw;
    caseIndex = WithdrawStruct.caseIndexWithdraw;
    pasteDate = WithdrawStruct.withdrawDate;
  }
  auto startDay = pasteDate.day();
  QString infoDepWithdraw = "Deposite for ";
  if (flag) infoDepWithdraw = "Withdraw for ";
  if (!summ.isEmpty()) {
    if (caseIndex == 0 || caseIndex == 1) {
      if (currentDate <= pasteDate && itterator >= pasteDate &&
          DepStruct.endDate >= pasteDate) {
        if (flag) {
          finalAmount -= summ.toDouble();
        } else {
          finalAmount += summ.toDouble();
        }
        anuInfo += infoDepWithdraw + QString::number(pasteDate.day()) + " " +
                   QLocale().monthName(pasteDate.month()) + " " +
                   QString::number(pasteDate.year()) + ": " +
                   QString::number(finalAmount, 'f', 2) +
                   " amount: " + QString::number(summ.toDouble(), 'f', 2) +
                   "\n";
        if (caseIndex == 1) {
          pasteDate = pasteDate.addMonths(1);
          fixDate(pasteDate, startDay);
        }
      }
    }
  }
}

void s21::CalcModel::debitCaseMonth(QDate& currentDate, QDate& itterator,
                                    unsigned short startCurrentDay) {
  currentDate = currentDate.addMonths(1);
  fixDate(currentDate, startCurrentDay);
  itterator = currentDate.addMonths(1);
  fixDate(itterator, startCurrentDay);
}

void s21::CalcModel::debitCaseWeek(QDate& currentDate, QDate& itterator,
                                   unsigned short& ittWeek) {
  if (currentDate.daysTo(DepStruct.endDate) <= ittWeek) {
    ittWeek = currentDate.daysTo(DepStruct.endDate);
  }
  currentDate = currentDate.addDays(ittWeek);
  itterator = currentDate.addDays(ittWeek);
}

void s21::CalcModel::outputDebit(QString& anuInfo, QString& summResult,
                                 QString& profitStr) {
  unsigned short daysOnYear = DepStruct.currentDate.daysTo(
                     DepStruct.currentDate.addYears(1)),
                 startCurrentDay = DepStruct.currentDate.day(), ittWeek = 7;
  double finalAmount = DepStruct.summ, profit = 0, interest = 0,
         interestRate = DepStruct.interestRate / 100 / daysOnYear;
  QDate itterator, currentDate = DepStruct.currentDate;

  while (currentDate.daysTo(DepStruct.endDate) > 0) {
    if (DepStruct.caseIndex == 1) {
      debitCaseMonth(currentDate, itterator, startCurrentDay);
    } else if (DepStruct.caseIndex == 0) {
      debitCaseWeek(currentDate, itterator, ittWeek);
    }

    if (DepStruct.isCapitalized) {
      interest = finalAmount * interestRate * currentDate.daysTo(itterator);
    } else {
      interest = DepStruct.summ * interestRate * currentDate.daysTo(itterator);
    }
    finalAmount += interest;
    profit += interest;

    QString currentYear = QString::number(currentDate.year());
    QString currentMonth = QLocale().monthName(currentDate.month());
    QString currentDay = QString::number(currentDate.day());

    anuInfo += "Total for " + currentDay + " " + currentMonth + " " +
               currentYear + ": " + QString::number(finalAmount, 'f', 2) +
               " profit: " + QString::number(interest, 'f', 2) + "\n";

    reDepositWithdrawCalculate(currentDate, ReDepositStruct.depositDate,
                               itterator, finalAmount, anuInfo, false);
    reDepositWithdrawCalculate(currentDate, WithdrawStruct.withdrawDate,
                               itterator, finalAmount, anuInfo, true);
  }
  summResult = QString::number(finalAmount, 'f', 2);
  profitStr = QString::number(profit, 'f', 2);
}

// CALCULATE GRAPH
void s21::CalcModel::outputGraph(QString& graphResult, QVector<double>& x,
                                 QVector<double>& y) {
  int h = GraphStruct.h * 300;
  double j = (GraphStruct.xEnd - GraphStruct.xStart) / h;
  for (int i = 0; i <= h; ++i) {
    try {
      QString replace = graphResult;
      x[i] = GraphStruct.xStart + i * j;
      QString num = QString::number(x[i]);
      replace.replace("X", num, Qt::CaseInsensitive);
      y[i] = calculate(replace);
    } catch (std::exception& e) {
      continue;
    }
  }
}

void s21::CalcModel::resizeGraph(QVector<double>& y, double& yStart,
                                 double& yEnd) {
  // get xy range
  for (int i = 0; i < y.size() && i < y.size(); i++) {
    if (y[i] > yEnd && fabs(y[i]) >= 0.000001) {
      yEnd = y[i];
    }
    if (y[i] < yStart && fabs(y[i]) >= 0.000001) {
      yStart = y[i];
    }
  }
}

// SETTERS STRUCTS
void s21::CalcModel::setGraphStructureValues(int h, double xStart,
                                             double xEnd) {
  GraphStruct.h = h;
  GraphStruct.xStart = xStart;
  GraphStruct.xEnd = xEnd;
}
void s21::CalcModel::setCreditStructureValues(double summ, double interestRate,
                                              unsigned short caseIndex,
                                              QDate currentDate,
                                              unsigned short months) {
  CreditStruct.summ = summ;
  CreditStruct.interestRate = interestRate;
  CreditStruct.caseIndex = caseIndex;
  CreditStruct.currentDate = currentDate;
  CreditStruct.months = months;
}

void s21::CalcModel::setDepStructureValues(double summ, double interestRate,
                                           unsigned short caseIndex,
                                           bool isCapitalized,
                                           QDate currentDate, QDate endDate) {
  DepStruct.summ = summ;
  DepStruct.interestRate = interestRate;
  DepStruct.caseIndex = caseIndex;
  DepStruct.isCapitalized = isCapitalized;
  DepStruct.currentDate = currentDate;
  DepStruct.endDate = endDate;
}

void s21::CalcModel::setReDepStructureValues(QString summDep, QDate depositDate,
                                             unsigned short caseIndexDep) {
  ReDepositStruct.summDep = summDep;
  ReDepositStruct.depositDate = depositDate;
  ReDepositStruct.caseIndexDep = caseIndexDep;
}

void s21::CalcModel::setWithdrawStructureValues(
    QString summWithdraw, QDate withdrawDate,
    unsigned short caseIndexWithdraw) {
  WithdrawStruct.summWithdraw = summWithdraw;
  WithdrawStruct.withdrawDate = withdrawDate;
  WithdrawStruct.caseIndexWithdraw = caseIndexWithdraw;
}