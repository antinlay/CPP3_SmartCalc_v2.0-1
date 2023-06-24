#ifndef DEBIT_H
#define DEBIT_H

#include <QWidget>

//namespace s21 {
QT_BEGIN_NAMESPACE
namespace Ui {
class Debit;
}
QT_END_NAMESPACE
class Debit : public QWidget {
  Q_OBJECT

 public:
  explicit Debit(QWidget *parent = nullptr);
  ~Debit();

 private slots:
  void on_pushButtonDebit_clicked();

 private:
  Ui::Debit *ui;
};

//}  // namespace s21

#endif  // DEBIT_H
