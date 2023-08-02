#include "calcModel.h"

bool s21::CalcModel::validateExpression(QString& expression) {
  QStack<QChar> parenthesesStack;

  // Проверка на сбалансированность скобок
  for (int i = 0; i < expression.length(); ++i) {
    QChar ch = expression.at(i);
    if (ch == '(')
      parenthesesStack.push(ch);
    else if (ch == ')') {
      if (parenthesesStack.empty()) return false;
      parenthesesStack.pop();
    }
  }
  if (!parenthesesStack.empty()) return false;

  // QDoubleValidator validator;
  // int pos = 0;
  // QValidator::State state = validator.validate(expression, pos);
  // return (state == QValidator::Acceptable);

  QRegularExpression validChars("[^0-9.(),+\\-*/^sqrtancolimdxX]+");
  if (validChars.match(expression).hasMatch()) return false;

  QRegularExpression regexAlphabet("[a-zA-ZА-я]+");
  if (regexAlphabet.match(expression).hasMatch()) {
    QRegularExpression regexFunc(
        "(sin|cos|tan|sqrt|asin|acos|atan|ln|log|mod)");
    if (!regexFunc.match(expression).hasMatch()) return false;

    //   QRegularExpression regexCloseBracket(
    //       "\\)(sin|cos|tan|sqrt|asin|acos|atan|ln|log|X|x|mod)");
    //   if (regexCloseBracket.match(expression).hasMatch()) return false;

    //   QRegularExpression regexBeforeFunc(
    //       "(\\d+(\\.\\d+)?(sin|cos|tan|sqrt|asin|acos|atan|ln|"
    //       "log))");
    //   if (regexBeforeFunc.match(expression).hasMatch()) return false;

    //   QRegularExpression regexBeforeX("(\\d+\\.?\\d*[Xx]|[Xx]\\d+\\.?\\d*)");
    //   if (regexBeforeX.match(expression).hasMatch()) return false;

    //   QRegularExpression multipleFunctions(
    //       "(?!sqrt\\()sqrt{1,}|(?!sin\\()sin{1,}|(?!cos\\()cos{1,}|(?!tan\\()tan{"
    //       "1,}|(?!asin\\()asin{1,}|(?!acos\\()acos{1,}|(?!atan\\()atan{1,}|(?!"
    //       "ln\\()ln{2,}|(?!log\\()log{1,}|(?!mod\\()mod{1,}|X{2,}|x{2,}|\\s{1,}");
    //   if (multipleFunctions.match(expression).hasMatch()) return false;

    //   QRegularExpression
    //   regexExponenta("[+-]?\\d+(\\.\\d+)?([eE][+-]?\\d+)?"); if
    //   (!regexExponenta.match(expression).hasMatch()) return false;
  }

  // QRegularExpression regexBracketDigit("\\)(?=\\d)");
  // if (regexBracketDigit.match(expression).hasMatch()) return false;
  // QRegularExpression regexDotMax(
  //     "\\d*\\.\\d+\\.(?!\\d)|\\d+\\.\\d+\\.\\d+|^\\.\\d+\\.\\d+");
  // if (regexDotMax.match(expression).hasMatch()) return false;
  // // Проверка на неправильное расположение операторов и функций
  // QRegularExpression invalidOperators(
  //     "(\\+\\+|\\+\\*|\\+\\/|\\+\\^|\\+\\-|\\*\\*|\\*\\/"
  //     "|\\*\\^|\\*\\-|\\/\\/|\\/\\*|\\/\\^|\\/\\-|\\^\\+|\\^\\*|\\^\\/"
  //     "|\\^\\^|\\^\\-|\\-\\+|\\-\\*|\\-\\/|\\-\\^|\\-\\-|\\(\\)|\\)\\()");
  // if (invalidOperators.match(expression).hasMatch()) return false;
  // // Проверка на неправильное количество операторов и функций
  // QRegularExpression multipleOperators(
  //     "\\+{2,}|\\-{2,}|\\*{2,}|\\/{2,}|\\^{2,}|\\.{2,}");
  // if (multipleOperators.match(expression).hasMatch()) return false;

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
  return fmod(a, b);
}

double s21::CalcModel::powerCalc(double a, double b) { return pow(a, b); }

double s21::CalcModel::sqrtCalc(double a) {
  if (a < 0) {
    throw std::runtime_error("Undefined square root of a negative number: " +
                             std::to_string(a));
  }

  return qSqrt(a);
}
// FUNCTIONS
double s21::CalcModel::lnCalc(double a) { return log(a); }
double s21::CalcModel::logCalc(double a) { return log10(a); }
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

bool s21::CalcModel::isDigit(QChar& currentChar, QString& infix, int& i) {
  bool result = false;
  if (currentChar.isDigit() || currentChar == '.' || currentChar == 'e' ||
      (currentChar == '-' &&
       (i == 0 || !infix[i - 1].isDigit() && infix[i - 1] != ')'))) {
    result = true;
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
  if (!operations.contains(c))
    throw std::invalid_argument("Input Error: " + c.toStdString() +
                                " not found");

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
  if (!functions.contains(c))
    throw std::invalid_argument("Input Error: " + c.toStdString() +
                                " not found");

  return (this->*functions.value(c))(a);
}

void s21::CalcModel::fixInfix(QString& infix) {
  for (auto it = keyFunctions.begin(); it != keyFunctions.end(); ++it) {
    int pos = 0;
    while ((pos = infix.indexOf(it.key(), pos)) != -1) {
      infix.replace(pos, it.key().length(), it.value());
      pos += it.value().length();
    }
  }
  QTextStream out(stdout);

  out << infix << Qt::endl;
}

// CONVERT TO POSTFIX
QQueue<QString> s21::CalcModel::infixToPostfix(QString& infix) {
  QStack<QString> operatorStack;
  QQueue<QString> outputQueue;
  QString currentToken = "";
  fixInfix(infix);

  for (int i = 0; i < infix.length(); i++) {
    QChar currentChar = infix[i];
    if (isDigit(currentChar, infix, i)) {
      if (currentChar == 'e') {
        currentToken += currentChar;
        currentChar = infix[++i];
      }
      currentToken += currentChar;
    } else {
      if (!currentToken.isEmpty()) {
        outputQueue.push_back(currentToken);
        currentToken = "";
      }
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
          outputQueue.push_back(operatorStack.top());
          operatorStack.pop();
        }
        operatorStack.push(QString(1, currentChar));
      }
    }
  }

  if (!currentToken.isEmpty()) {
    outputQueue.push_back(currentToken);
  }

  while (!operatorStack.empty()) {
    outputQueue.push_back(operatorStack.top());
    operatorStack.pop();
  }
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
  QString token;
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

double s21::CalcModel::calculate(QString infix) {
  QQueue<QString> newInfix = infixToPostfix(infix);
  return calculatePostfix(newInfix);
}

void s21::CalcModel::paymentAnnuityCalc(double& p, double& P) {
  /* Кредитный калькулятор с аннуитетными платежами можно рассчитать по
   следующей формуле: p = (S * i * (1 + i)^n) / ((1 + i)^n - 1)? где: p -
   размер ежемесячного платежа, S - сумма кредита, i - процентная ставка в
   месяц,  n - количество месяцев, O - общая переплата, o - месячная
   переплата, P - обшая переплата */
  short n = CreditStruct.months;
  double S = CreditStruct.summ, i = CreditStruct.interestRate;
  p = (S * (i * qPow((1 + i), n))) / (qPow((1 + i), n) - 1);
  P = S * n;
}

void s21::CalcModel::paymentDifferentialCalc(double& p, double& o, size_t m) {
  /* Формула для расчета дифференцированного платежа выглядит следующим
   образом : P = (S / n) + (S - (m - 1) * (S / n)) * i, где: P - размер
   дифференцированного платежа, S - сумма кредита, n - срок кредита в
   месяцах, m - номер текущего месяца, i - годовая процентная ставка,
   деленная на 12 месяцев. i = (S - (m - 1) * (S / n)) * i */
  double S = CreditStruct.summ, i = CreditStruct.interestRate;
  size_t n = CreditStruct.months;
  p = (S / n) + (S - (m - 1) * (S / n)) * i;
  o = (S - (m - 1) * (S / n)) * i;
}

void s21::CalcModel::outputCredit(QString& anuInfo, QString& payment,
                                  QString& overpayment) {
  short m = 1;
  double o = 0, O = 0, p = CreditStruct.summ, P = CreditStruct.interestRate;
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
        if (flag)
          finalAmount -= summ.toDouble();
        else
          finalAmount += summ.toDouble();
        anuInfo += infoDepWithdraw + QString::number(pasteDate.day()) + " " +
                   QLocale().monthName(pasteDate.month()) + " " +
                   QString::number(pasteDate.year()) + ": " +
                   QString::number(finalAmount, 'f', 2) +
                   " amount: " + QString::number(summ.toDouble(), 'f', 2) +
                   "\n";
        if (caseIndex == 1) {
          pasteDate = pasteDate.addMonths(1);
          if (pasteDate.month() != 2 || startDay == 31)
            pasteDate.setDate(pasteDate.year(), pasteDate.month(),
                              pasteDate.daysInMonth());
        }
      }
    }
  }
}

void s21::CalcModel::fixDate(QDate& fixDate, short startCurrentDay) {
    if (fixDate.month() == 2 || startCurrentDay == 31)
      fixDate.setDate(fixDate.year(), fixDate.month(),
                          fixDate.daysInMonth());
}

void s21::CalcModel::debitCaseMonth(QDate& currentDate, QDate& itterator, short startCurrentDay) {
      currentDate = currentDate.addMonths(1);
      fixDate(currentDate, startCurrentDay);
      itterator = currentDate.addMonths(1);
      if (itterator.month() == 2 || startCurrentDay == 31)
        itterator.setDate(itterator.year(), itterator.month(),
                          itterator.daysInMonth());
}

void s21::CalcModel::debitCaseWeek(QDate& currentDate, QDate& itterator, short& ittWeek) {
      if (currentDate.daysTo(DepStruct.endDate) <= ittWeek) {
        ittWeek = currentDate.daysTo(DepStruct.endDate);
      }
      currentDate = currentDate.addDays(ittWeek);
      itterator = currentDate.addDays(ittWeek);
}

void s21::CalcModel::outputDebit(QString& anuInfo, QString& summResult,
                                 QString& profitStr) {
  short daysOnYear = DepStruct.currentDate.daysTo(DepStruct.currentDate.addYears(1)), startCurrentDay = DepStruct.currentDate.day(), ittWeek = 7;
  double finalAmount = DepStruct.summ, profit = 0,
         interestRate = DepStruct.interestRate / 100 / daysOnYear;
  QDate itterator, currentDate = DepStruct.currentDate,
                   endDate = DepStruct.endDate;

  if (DepStruct.caseIndex == 1) {
      debitCaseMonth(currentDate, itterator, startCurrentDay);
  } else if (DepStruct.caseIndex == 0) {
      debitCaseWeek(currentDate, itterator, ittWeek);
  }

  while (currentDate.daysTo(DepStruct.endDate) > 0) {
    double interest;

    if (DepStruct.isCapitalized) {
      qDebug() << currentDate.daysTo(itterator) << "CD to ITT";
      interest = finalAmount * interestRate * currentDate.daysTo(itterator);
      qDebug() << interest << "CD to ITT";
    } else {
      interest = DepStruct.summ * interestRate * currentDate.daysTo(itterator);
    }
    finalAmount += interest;
    profit += interest;
    qDebug() << finalAmount << "FA";
    qDebug() << profit << "PR";

    QString currentYear = QString::number(currentDate.year());
    QString currentMonth = QLocale().monthName(currentDate.month());
    QString currentDay = QString::number(currentDate.day());

    anuInfo += "Pay for " + currentDay + " " + currentMonth + " " +
               currentYear + ": " + QString::number(finalAmount, 'f', 2) +
               " interest: " + QString::number(interest, 'f', 2) + "\n";
    qDebug() << currentDate.daysTo(endDate) << "CR - ED";
    qDebug() << ittWeek << "ITT";

    reDepositWithdrawCalculate(currentDate, ReDepositStruct.depositDate,
                               itterator, finalAmount, anuInfo, false);
    reDepositWithdrawCalculate(currentDate, WithdrawStruct.withdrawDate,
                               itterator, finalAmount, anuInfo, true);
  }
  summResult = QString::number(finalAmount, 'f', 2);
  profitStr = QString::number(profit, 'f', 2);
}

void s21::CalcModel::graphCalculate(int& h, double& xStart, double& yStart,
                                    double& xEnd, double& yEnd,
                                    QString graphResult, QVector<double>& x,
                                    QVector<double>& y) {
  double j = (xEnd - xStart) / h;
  for (int i = 0; i <= h; ++i) {
    try {
      QString replace = graphResult;
      x[i] = xStart + i * j;
      QString num = QString::number(x[i]);
      replace.replace("X", num, Qt::CaseInsensitive);
      y[i] = calculate(replace);
    } catch (std::exception& e) {
      x.remove(i);
      --i;
      continue;
    }
  }
  // get xy range
  for (int i = 0; i < y.size() && i < x.size(); i++) {
    if (y[i] > yEnd && y[i] >= 0.000001) {
      yEnd = y[i];
    }

    if (y[i] < yStart && y[i] >= 0.000001) {
      yStart = y[i];
    }
  }
  // xStart = *qMin(x.constBegin(), x.constEnd());
  // xEnd = *qMax(x.constBegin(), x.constEnd());
  // yStart = *qMin(y.constBegin(), y.constEnd());
  // yEnd = *qMax(y.constBegin(), y.constEnd());
}
