#include "calcModel.h"

void CalcModel::add(double a) { data += a; }

void CalcModel::mult(double a) { data *= a; }

void CalcModel::reset() { data = 0; }

double CalcModel::getData() { return data; }