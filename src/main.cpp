#include <cmath>
#include <iostream>
#include <stack>
#include <unordered_map>

using namespace std;

// Функция, которая проверяет, является ли символ оператором
bool is_operator(const char& c) {
  static const string operators = "+-*/%^";
  return operators.find(c) != string::npos;
}

double calculate(double a, double b, char c) {
  double res{};
  try {
    switch (c) {
      case '+':
        res = a + b;
        break;
      case '-':
        res = a - b;
        break;
      case '*':
        res = a * b;
        break;
      case '/':
        res = a / b;
        break;
      case '%':
        if (b == 0) {
          throw("Error");
        } else {
          res = fmod(a, b);
        }
        break;
      case '^':
        res = pow(a, b);
        break;
    }
  } catch (...) {
    throw("Error");
  }
  return res;
}

// Return precedence of operators
int precedence(const char& c) {
  static const unordered_map<char, int> precedences = {
      {'+', 1}, {'-', 1}, {'*', 2}, {'/', 2}, {'%', 2}, {'^', 3}, {'(', 0}};
  return precedences.at(c);
}

// Infix to postfix
string to_postfix(const string& infix) {
  stack<char> s;
  string postfix = "";
  for (const char& c : infix) {
    if (isdigit(c)) {
      postfix += c;
    } else if (c == '(') {
      s.push(c);
    } else if (c == ')') {
      while (!s.empty() && s.top() != '(') {
        postfix += s.top();
        s.pop();
      }
      s.pop();  // Удаляем открывающую скобку из стека
    } else if (is_operator(c)) {
      while (!s.empty() && is_operator(s.top()) &&
             precedence(s.top()) >= precedence(c)) {
        postfix += s.top();
        s.pop();
      }
      s.push(c);
    }
  }
  // Добавляем оставшиеся операторы в выходную строку
  while (!s.empty()) {
    postfix += s.top();
    s.pop();
  }
  return postfix;
}

int main() {
  string infix = "3 + 4 * 2 / (1 - 5) ^ 2";
  string postfix = to_postfix(infix);
  cout << "Infix: " << infix << endl;
  cout << "Postfix: " << postfix << endl;

  stack<double> operands;  // стек операндов
                           //   string expression = "23+4*";
  for (char c : postfix) {
    if (isdigit(c)) {
      operands.push(
          c - '0');  // преобразование символа в число и помещение его в стек
    } else {
      double operand2 =
          operands.top();  // извлечение последнего операнда из стека
      operands.pop();
      double operand1 =
          operands.top();  // извлечение предпоследнего операнда из стека
      operands.pop();
      operands.push(calculate(operand1, operand2, c));
    }
  }

  cout << "Result: " << operands.top() << endl;  // вывод результата вычисления
  return 0;
}
// #include "consoleView.h"

// int main() {
//     ExampleModel model;
//     ExampleController controller(&model);
//     ConsoleView view(&controller);
//     view.startEventLoop();
//     return 1;
// }