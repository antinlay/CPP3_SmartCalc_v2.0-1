#include "calcController.h"

void s21::CalcController::calcExpression(QString& equalResult,
                                         QString& equalX) {
  if (equalResult.contains("X", Qt::CaseInsensitive) &&
      !equalX.contains("X", Qt::CaseInsensitive)) {
    equalResult =
        equalResult.replace("X", "(" + equalX + ")", Qt::CaseInsensitive);
  }
  double result = resultModel.calculate(equalResult.toStdString());
  equalResult = QString::number(result, 'g', 14);
}

bool s21::CalcController::validateChangeOn(QString equalStr) {
  return resultModel.validateExpression(equalStr.toStdString());
}

void s21::CalcController::calcGraph(QString& graphResult, double& result) {
  result = resultModel.calculate(graphResult.toStdString());
}