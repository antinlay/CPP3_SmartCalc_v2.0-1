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

  QRegularExpression regexAlphabet("[a-zA-ZА-я]+");
  if (regexAlphabet.match(expression).hasMatch()) {
    QRegularExpression regexFunc(
        "(sin|cos|tan|sqrt|asin|acos|atan|ln|log|mod)");
    if (!regexFunc.match(expression).hasMatch()) return false;

    QRegularExpression regexCloseBracket(
        "\\)(sin|cos|tan|sqrt|asin|acos|atan|ln|log|X|x|mod)");
    if (regexCloseBracket.match(expression).hasMatch()) return false;

    QRegularExpression regexBeforeFunc(
        "(\\d+(\\.\\d+)?(sin|cos|tan|sqrt|asin|acos|atan|ln|"
        "log))");
    if (regexBeforeFunc.match(expression).hasMatch()) return false;

    QRegularExpression regexBeforeX("(\\d+\\.?\\d*[Xx]|[Xx]\\d+\\.?\\d*)");
    if (regexBeforeX.match(expression).hasMatch()) return false;

    QRegularExpression multipleFunctions(
        "(?!sqrt\\()sqrt{1,}|(?!sin\\()sin{1,}|(?!cos\\()cos{1,}|(?!tan\\()tan{"
        "1,}|(?!asin\\()asin{1,}|(?!acos\\()acos{1,}|(?!atan\\()atan{1,}|(?!"
        "ln\\()ln{2,}|(?!log\\()log{1,}|(?!mod\\()mod{1,}|X{2,}|x{2,}|\\s{1,}");
    if (multipleFunctions.match(expression).hasMatch()) return false;

    // QRegularExpression
    // regexExponenta("[+-]?\\d+(\\.\\d+)?([eE][+-]?\\d+)?");
    //  if (!regexExponenta.match(expression).hasMatch()) return false;
  }

  QRegularExpression regexBracketDigit("\\)(?=\\d)");
  if (regexBracketDigit.match(expression).hasMatch()) return false;
  QRegularExpression regexDotMax(
      "\\d*\\.\\d+\\.(?!\\d)|\\d+\\.\\d+\\.\\d+|^\\.\\d+\\.\\d+");
  if (regexDotMax.match(expression).hasMatch()) return false;
  // Проверка на неправильное расположение операторов и функций
  QRegularExpression invalidOperators(
      "(\\+\\+|\\+\\*|\\+\\/|\\+\\^|\\+\\-|\\*\\*|\\*\\/"
      "|\\*\\^|\\*\\-|\\/\\/|\\/\\*|\\/\\^|\\/\\-|\\^\\+|\\^\\*|\\^\\/"
      "|\\^\\^|\\^\\-|\\-\\+|\\-\\*|\\-\\/|\\-\\^|\\-\\-|\\(\\)|\\)\\()");
  if (invalidOperators.match(expression).hasMatch()) return false;
  // Проверка на неправильное количество операторов и функций
  QRegularExpression multipleOperators(
      "\\+{2,}|\\-{2,}|\\*{2,}|\\/{2,}|\\^{2,}|\\.{2,}");
  if (multipleOperators.match(expression).hasMatch()) return false;

  return true;
}

double s21::CalcModel::addCalc(double a, double b) { return a + b; }
double s21::CalcModel::subtractCalc(double a, double b) { return a - b; }
double s21::CalcModel::multiplyCalc(double a, double b) { return a * b; }
double s21::CalcModel::divideCalc(double a, double b) {
  if (b == 0) {
    if (b == 0) {
      throw std::runtime_error("Undefined divide zero: " + std::to_string(a) +
                               " / " + std::to_string(b));
    }
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

  return qSqrt(qAbs(a));
}
// FUNCTIONS
double s21::CalcModel::lnCalc(double a) { return log(a); }
double s21::CalcModel::logCalc(double a) { return log10(a); }
double s21::CalcModel::tanCalc(double a) {
  a = getDegreeMode(a);
  return tan(a);
}
double s21::CalcModel::atanCalc(double a) {
  a = getDegreeMode(a);
  return atan(a);
}
double s21::CalcModel::sinCalc(double a) {
  a = getDegreeMode(a);
  return sin(a);
}
double s21::CalcModel::asinCalc(double a) {
  a = getDegreeMode(a);
  return asin(a);
}
double s21::CalcModel::cosCalc(double a) {
  a = getDegreeMode(a);
  return cos(a);
}
double s21::CalcModel::acosCalc(double a) {
  a = getDegreeMode(a);
  return acos(a);
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
  QRegularExpression pattern("(\\d+\\.?\\d*)([a-zA-Z]+)");
  QString modifiedExpression = infix.replace(pattern, "$1*$2");

  for (auto it = keyFunctions.begin(); it != keyFunctions.end(); ++it) {
    int pos = 0;
    while ((pos = infix.indexOf(it.key(), pos)) != -1) {
      infix.replace(pos, it.key().length(), it.value());
      pos += it.value().length();
    }
  }
}

// CONVERT TO POSTFIX
QQueue<QString> s21::CalcModel::infixToPostfix(QString& infix) {
  QStack<QString> operatorStack;
  QQueue<QString> outputQueue;
  QString currentToken = "";
  if (!infix.isEmpty()) {
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

QString s21::CalcModel::creditCalculate(QString& overPayment,
                                        QString& allPayment, int month,
                                        double summa, QString stavkaProc,
                                        QString sumCredit, QString spinBox,
                                        size_t comboBox) {
  double payment = 0, allSum = 0, pp = 0;
  QString result;

  if (stavkaProc == "" || sumCredit == "" || spinBox == "") {
    return "ERROR";
  } else {
    double summaProc = summa;

    for (int var = 1; var <= month; var++) {
      double stavka = stavkaProc.toDouble();
      QString payInfo, monthPay;
      if (comboBox == 1) {
        // https://www.banki.ru/wikibank/raschet_differentsirovannogo_plateja/
        // in 31 days on month and 365 days on year
        QString varMonth = QString::number(var);
        payment = summa / month + summaProc * stavka * 31 / 365 / 100;
        allSum += payment;
        summaProc = summa - var * summa / month;
        monthPay = QString::number(payment, 'f', 2);
        payInfo = "Pay for " + varMonth + " month = " + monthPay + "\n";
      } else if (comboBox == 0) {
        // https://www.banki.ru/wikibank/raschet_annuitetnogo_plateja/
        var = month;
        double prStavka = stavka / 12 / 100;
        payment = summa * (prStavka * pow(1 + prStavka, month) /
                           (pow(1 + prStavka, month) - 1));
        allSum = payment * month;
        monthPay = QString::number(payment, 'f', 2);
        payInfo = "Pay for every month = " + monthPay + "\n";
        //                ui->listWidget->setMaximumSize(6, 6);
      }

      result += payInfo;
    }
    pp = allSum - summa;
    overPayment = QString::number(pp, 'f', 2);
    allPayment = QString::number(allSum, 'f', 2);
  }
  return result;
}

QString s21::CalcModel::debitCalculate(double& resProfit, double& resDep,
                                       double sumDep, double percent, int month,
                                       bool checkState) {
  double resPercent = month / 12, profit = 0;
  resProfit = (sumDep * percent * resPercent) / 100,
  resDep = sumDep + resProfit;
  QString result;

  for (int var = 1; var <= month; ++var) {
    QString depInfo, qDeposit, qProfit;
    QString varMonth = QString::number(var);
    resPercent = varMonth.toDouble() / 12;

    if (checkState == false) {
      // https://www.sravni.ru/vklady/info/kak-rasschitat-procenty-po-vklady/
      profit = (sumDep * percent * resPercent) / 100;

    } else {
      profit = (sumDep * percent * resPercent) / 100;
      sumDep = sumDep + profit;
      //            sumDep = allDeposit;
    }
    double allDeposit = sumDep + profit;
    qDeposit = QString::number(allDeposit, 'f', 2);
    qProfit = QString::number(profit, 'f', 2);
    depInfo = "Deposit for " + varMonth + " month = " + qDeposit +
              " and profit = " + qProfit + "\n";
    result += depInfo;
  }
  return result;
}

void s21::CalcModel::graphCalculate(int& h, double& xStart, double& yStart,
                                    double& xEnd, double& yEnd,
                                    QString graphResult, QVector<double>& x,
                                    QVector<double>& y) {
  double j = (xEnd - xStart) / h;
  for (int i = 0; i <= h; ++i) {
    // double x = xStart + i * j;
    QString replace = graphResult;
    x[i] = xStart + i * j;
    QString num = QString::number(x[i]);
    replace.replace("X", num, Qt::CaseInsensitive);
    y[i] = calculate(replace);
  }

  for (int i = 0; i < y.size() && i < x.size(); i++) {
    if (y[i] > yEnd && y[i] >= 0.000001) {
      yEnd = y[i];
    }

    if (y[i] < yStart && y[i] >= 0.000001) {
      yStart = y[i];
    }
  }
  std::cout << yStart << " Y " << yEnd << std::endl;
  std::cout << xStart << " X " << xEnd << std::endl;
}
