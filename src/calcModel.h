#ifndef CALCMODEL_H
#define CALCMODEL_H

class CalcModel {
 private:
  double data;

 public:
  CalcModel() : data(0){};
  void add(double a);
  void mult(double a);
  void reset();
  double getData();
};

#endif