#include <QApplication>
#include <QDoubleValidator>

#include "calcView.h"

int main(int argc, char *argv[]) {
  QApplication a(argc, argv);
  s21::calcView w;
  w.show();
  return a.exec();
}
