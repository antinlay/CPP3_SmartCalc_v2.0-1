#include <QApplication>
#include <QDoubleValidator>

#include "calcView.h"
#include "calcController.h"
#include "calcModel.h"

int main(int argc, char *argv[]) {
  QApplication a(argc, argv);

  s21::CalcModel *m;
  Ui::CalcView *w;
  s21::CalcController c(w, m);

  QObject::connect(&w, handleUiEvent(/* Параметры события */), &c, handleUiEvent(/* Параметры события */));

  CalcView v;
  v.show();

  return a.exec();
}
