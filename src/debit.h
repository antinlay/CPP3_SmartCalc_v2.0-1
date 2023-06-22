#ifndef DEBIT_H
#define DEBIT_H

#include <QWidget>

namespace Ui {
class Debit;
}

class Debit : public QWidget {
  Q_OBJECT

 public:
  explicit Debit(QWidget *parent = nullptr);
  ~Debit();

 private slots:
  void on_debit_clicked();

 private:
  Ui::Debit *ui;
};

#endif  // DEBIT_H
