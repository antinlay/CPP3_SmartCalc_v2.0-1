#include "calcController.h"

int main(int argc, char *argv[]) {
  QApplication a(argc, argv);

  s21::CalcModel m;
  Ui::CalcView v;
  s21::CalcController c(&m, &v);

  // SHOW && CONNECT VIEW
  CalcView w;
  w.show();
  QObject::connect(&w, &CalcView::uiEventEqual, &c,
                   &s21::CalcController::calcEqual);
  QObject::connect(&w, &CalcView::validateChangedOn, &c,
                   &s21::CalcController::validateChangeOn);
  QObject::connect(&w, &CalcView::uiEventSendUi, &c, &s21::CalcController::sendCalcViewUi);
  // CONNECT GRAPH
  Graph g;
  QObject::connect(&g, &Graph::uiEventOutputGraph, &c,
                   &s21::CalcController::graphOutput);
  QObject::connect(&g, &Graph::uiEventResizeGraph, &c,
                   &s21::CalcController::graphResize);
  QObject::connect(&w, &CalcView::uiEventReplaceX, &c,
                   &s21::CalcController::replaceX);
  QObject::connect(&w, &CalcView::uiEventSendResult, &g,
                   &Graph::sendResult);
  QObject::connect(&g, &Graph::uiEventSendUi, &c, &s21::CalcController::sendGraphUi);

  // CONNECT CREDIT
  Credit r;
  QObject::connect(&r, &Credit::uiEventOutputInfo, &c,
                   &s21::CalcController::creditOutputInfo);
  QObject::connect(&w, &CalcView::uiEventShowCredit, &r, &Credit::showCredit);
  QObject::connect(&r, &Credit::uiEventSendUi, &c, &s21::CalcController::sendCreditUi);

  // CONNECT DEBIT
  Debit t;
  QObject::connect(&t, &Debit::uiEventOutputInfo, &c,
                   &s21::CalcController::outputDebitInfo);
  QObject::connect(&w, &CalcView::uiEventShowDebit, &t, &Debit::showDebit);
  QObject::connect(&t, &Debit::uiEventSendUi, &c, &s21::CalcController::sendDebitUi);

  return a.exec();
}
