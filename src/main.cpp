#include <QApplication>
#include <QDoubleValidator>

#include "calcController.h"

int main(int argc, char *argv[]) {
  QApplication a(argc, argv);

  s21::CalcModel m;
  Ui::CalcView v;
  s21::CalcController c(&v, &m);

  CalcView w;
  w.show();

  QObject::connect(&w, &CalcView::setDegreeMode, &c,
                   &s21::CalcController::setDegreeMode);

  QObject::connect(&w, &CalcView::uiEventEqual, &c,
                   &s21::CalcController::calcEqual);

  QObject::connect(&w, &CalcView::validateChangedOn, &c,
                   &s21::CalcController::validateChangeOn);
  Graph g;
  QObject::connect(&g, &Graph::uiEventGraph, &c,
                   &s21::CalcController::calcGraph);
  QObject::connect(&w, &CalcView::uiEventReplaceX, &c,
                   &s21::CalcController::replaceX);
  QObject::connect(&w, &CalcView::uiEventSendResult, &g,
                   &Graph::uiEventSendResult);

  Credit r;
  QObject::connect(&r, &Credit::uiEventAnnuityCalc, &c,
                   &s21::CalcController::creditAnnuityCalc);
  QObject::connect(&r, &Credit::uiEventDifferentialCalc, &c,
                   &s21::CalcController::creditDifferentialCalc);
  QObject::connect(&w, &CalcView::uiEventShowCredit, &r, &Credit::showCredit);

  return a.exec();
}
