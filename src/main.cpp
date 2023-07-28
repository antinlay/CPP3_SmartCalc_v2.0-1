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

  QObject::connect(&w, &CalcView::setDegreeMode , &c,
                   &s21::CalcController::setDegreeMode);

  QObject::connect(&w, &CalcView::uiEventEqual, &c,
                   &s21::CalcController::calcEqual);

  QObject::connect(&w, &CalcView::validateChangedOn, &c,
                   &s21::CalcController::validateChangeOn);
  Graph g;
  QObject::connect(&g, &Graph::uiEventGraph, &c,
                   &s21::CalcController::calcGraph);
  QObject::connect(&w, &CalcView::uiEventReplaceX, &c, &s21::CalcController::replaceX);
  QObject::connect(&w, &CalcView::uiEventSendResult, &g, &Graph::uiEventSendResult);

  Credit r;
  QObject::connect(&r, &Credit::uiEventPaymentCalc, &c, &s21::CalcController::uiEventPaymentCalc);
  QObject::connect(&r, &Credit::uiEventOverpaymentCalc, &c, &s21::CalcController::uiEventOverpaymentCalc);

  return a.exec();
}
