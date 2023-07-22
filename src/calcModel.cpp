#include "calcModel.h"

bool s21::CalcModel::validateExpression(QString& expression) {
  std::stack<char> parenthesesStack;

  // Проверка на сбалансированность скобок
  for (int i = 0; i < str.length(); ++i) {
    QChar ch = str.at(i);
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

  // std::regex regexAlphabet("[a-zA-ZА-я]+");
  // if (std::regex_search(expression, regexAlphabet)) {
  //   std::regex regexFunc("(sin|cos|tan|sqrt|asin|acos|atan|ln|log|mod)");
  //   if (!std ::regex_search(expression, regexFunc)) return false;

  //   std::regex regexCloseBracket(
  //       "\\)(sin|cos|tan|sqrt|asin|acos|atan|ln|log|X|x|mod)");
  //   if (std ::regex_search(expression, regexCloseBracket)) return false;

  //   std::regex regexBeforeFunc(
  //       "(\\d+(\\.\\d+)?(sin|cos|tan|sqrt|asin|acos|atan|ln|"
  //       "log))");
  //   if (std ::regex_search(expression, regexBeforeFunc)) return false;

  //   std::regex regexBeforeX("(\\d+\\.?\\d*[Xx]|[Xx]\\d+\\.?\\d*)");
  //   if (std ::regex_search(expression, regexBeforeX)) return false;

  //   std::regex multipleFunctions(
  //       "(?!sqrt\\()sqrt{1,}|(?!sin\\()sin{1,}|(?!cos\\()cos{1,}|(?!tan\\()tan{"
  //       "1,}|(?!asin\\()asin{1,}|(?!acos\\()acos{1,}|(?!atan\\()atan{1,}|(?!"
  //       "ln\\()ln{2,}|(?!log\\()log{1,}|(?!mod\\()mod{1,}|X{2,}|x{2,}|\\s{1,}");
  //   if (std::regex_search(expression, multipleFunctions)) return false;

  //   // std::regex regexExponenta("[+-]?\\d+(\\.\\d+)?([eE][+-]?\\d+)?");
  //   // if (!std ::regex_search(expression, regexExponenta)) return false;
  // }

  // std::regex regexBracketDigit("\\)(?=\\d)");
  // if (std ::regex_search(expression, regexBracketDigit)) return false;

  // std::regex regexDotMax(
  //     "\\d*\\.\\d+\\.(?!\\d)|\\d+\\.\\d+\\.\\d+|^\\.\\d+\\.\\d+");
  // if (std ::regex_search(expression, regexDotMax)) return false;

  // // Проверка на неправильное расположение операторов и функций
  // std::regex invalidOperators(
  //     "(\\+\\+|\\+\\*|\\+\\/|\\+\\^|\\+\\-|\\*\\*|\\*\\/"
  //     "|\\*\\^|\\*\\-|\\/\\/|\\/\\*|\\/\\^|\\/\\-|\\^\\+|\\^\\*|\\^\\/"
  //     "|\\^\\^|\\^\\-|\\-\\+|\\-\\*|\\-\\/|\\-\\^|\\-\\-|\\(\\)|\\)\\()");
  // if (std::regex_search(expression, invalidOperators)) return false;

  // // Проверка на неправильное количество операторов и функций
  // std::regex multipleOperators(
  //     "\\+{2,}|\\-{2,}|\\*{2,}|\\/{2,}|\\^{2,}|\\.{2,}");
  // if (std::regex_search(expression, multipleOperators)) return false;

  // return true;
}

// CHECKS
int s21::CalcModel::getPriority(std::string c) {
  int res = 0;
  if (isFunction(c)) {
    res = 4;
  } else {
    res = precedences.at(c);
  }
  return res;
}

bool s21::CalcModel::isDigit(char& currentChar, std::string& infix, int& i) {
  bool result = false;
  if (isdigit(currentChar) || currentChar == '.' || currentChar == 'e' ||
      (currentChar == '-' &&
       (i == 0 || !isdigit(infix[i - 1]) && infix[i - 1] != ')'))) {
    result = true;
  }
  return result;
}

bool s21::CalcModel::isOperator(const std::string& str) {
  bool result = false;
  if (!str.empty()) {
    std::string listOperators = "+-*/%^";
    if (listOperators.find(str) != std::string::npos) result = true;
  }
  return result;
}

bool s21::CalcModel::isFunction(const std::string& str) {
  bool result = false;
  if (!str.empty()) {
    std::string listOperators = "qgaiontsc";
    if (listOperators.find(str) != std::string::npos) result = true;
  }
  return result;
}

// MAP CALCULATIONS
double s21::CalcModel::calcOperations(double a, double b, std::string c) {
  std::map<std::string, std::function<double(s21::CalcModel*, double, double)>>
      operations = {{"+", &s21::CalcModel::addCalc},
                    {"-", &s21::CalcModel::subtractCalc},
                    {"*", &s21::CalcModel::multiplyCalc},
                    {"/", &s21::CalcModel::divideCalc},
                    {"%", &s21::CalcModel::modCalc},
                    {"^", &s21::CalcModel::powerCalc}};
  if (operations.find(c) == operations.end())
    throw std::invalid_argument("Input Error: " + c + " not found");
  else
    return operations[c](this, a, b);
}

double s21::CalcModel::calcFunctions(double a, std::string c) {
  std::map<std::string, std::function<double(s21::CalcModel*, double)>>
      functions = {
          {"q", &s21::CalcModel::sqrtCalc}, {"n", &s21::CalcModel::lnCalc},
          {"g", &s21::CalcModel::logCalc},  {"t", &s21::CalcModel::tanCalc},
          {"a", &s21::CalcModel::atanCalc}, {"s", &s21::CalcModel::sinCalc},
          {"i", &s21::CalcModel::asinCalc}, {"c", &s21::CalcModel::cosCalc},
          {"o", &s21::CalcModel::acosCalc}};
  if (functions.find(c) == functions.end())
    throw std::invalid_argument("Input Error: " + c + "not found");
  else
    return functions[c](this, a);
}

void s21::CalcModel::fixInfix(std::string& infix) {
  std::regex pattern("(\\d+\\.?\\d*)([a-zA-Z]+)");
  std::string modifiedExpression = std::regex_replace(infix, pattern, "$1*$2");

  static const std::unordered_map<std::string, std::string> keyFunctions = {
      {"sqrt", "q"}, {"ln", "n"},  {"log", "g"},  {"tan", "t"},
      {"atan", "a"}, {"sin", "s"}, {"asin", "i"}, {"cos", "c"},
      {"acos", "o"}, {"mod", "%"}, {"x", "X"}};
  for (auto& key : keyFunctions) {
    size_t pos = 0;
    while ((pos = infix.find(key.first, pos)) != std::string::npos) {
      infix.replace(pos, key.first.length(), key.second);
      pos += key.second.length();
    }
  }
}

// CONVERT TO POSTFIX
std::queue<std::string> s21::CalcModel::infixToPostfix(std::string& infix) {
  std::stack<std::string> operatorStack;
  std::queue<std::string> outputQueue;
  std::string currentToken = "";
  fixInfix(infix);

  for (int i = 0; i < infix.length(); i++) {
    char currentChar = infix[i];
    if (isDigit(currentChar, infix, i)) {
      if (currentChar == 'e') {
        currentToken += currentChar;
        currentChar = infix[++i];
      }
      currentToken += currentChar;
    } else {
      if (!currentToken.empty()) {
        outputQueue.push(currentToken);
        currentToken = "";
      }
      if (currentChar == '(') {
        operatorStack.push(std::string(1, currentChar));
      } else if (currentChar == ')') {
        while (operatorStack.top() != "(") {
          outputQueue.push(operatorStack.top());
          operatorStack.pop();
        }
        operatorStack.pop();
        // } else if (isFunction(infix.substr(i, 1))) {
        //   if (i == 0) operatorStack.push(infix.substr(i, 1));
      } else {
        while (!operatorStack.empty() && operatorStack.top() != "(" &&
               getPriority(std::string(1, currentChar)) <=
                   getPriority(operatorStack.top())) {
          outputQueue.push(operatorStack.top());
          operatorStack.pop();
        }
        operatorStack.push(std::string(1, currentChar));
      }
    }
  }

  if (!currentToken.empty()) {
    outputQueue.push(currentToken);
  }

  while (!operatorStack.empty()) {
    // if (operatorStack.top() == "(") {
    //   std::cout << "Error: mismatched paranthesis";
    //   std::exit(1);
    // }
    outputQueue.push(operatorStack.top());
    operatorStack.pop();
  }
  std::cout << std::endl;

  return outputQueue;
}

// CALCULATE POSTFIX
double s21::CalcModel::getFromStack(std::stack<double>& operands) {
  double operand = 0;
  if (!operands.empty()) {
    operand = operands.top();
    operands.pop();
  }
  return operand;
}

double s21::CalcModel::calculatePostfix(std::queue<std::string> postfix) {
  std::stack<double> calcStack;
  std::string token;
  while (!postfix.empty()) {
    token = postfix.front();
    std::cout << token << " ";
    postfix.pop();
    if (isOperator(token)) {
      double operand1 = getFromStack(calcStack);
      double operand2 = getFromStack(calcStack);
      double result = calcOperations(operand2, operand1, token);
      calcStack.push(result);
    } else if (isFunction(token)) {
      double topStack = getFromStack(calcStack);
      double debug = calcFunctions(topStack, token);
      calcStack.push(debug);
    } else {
      double debug = std::stod(token);
      calcStack.push(debug);
    }
  }
  return calcStack.top();
}

double s21::CalcModel::calculate(std::string infix) {
  std::queue<std::string> newInfix = infixToPostfix(infix);
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
