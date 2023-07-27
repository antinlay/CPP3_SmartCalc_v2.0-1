#ifndef DEBIT_H
#define DEBIT_H

#include <QWidget>

QT_BEGIN_NAMESPACE
namespace Ui {
class Debit;
}
QT_END_NAMESPACE
// namespace s21 {
class Debit : public QWidget {
  Q_OBJECT

 public:
  explicit Debit(QWidget *parent = nullptr);
  ~Debit();

 private slots:
  void debitClicked();
  
 private:
  Ui::Debit *ui;
};

// }  // namespace s21

#endif  // DEBIT_H
