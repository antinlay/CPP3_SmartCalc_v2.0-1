#ifndef CREDIT_H
#define CREDIT_H

#include <QWidget>

//namespace s21 {
QT_BEGIN_NAMESPACE
namespace Ui {
class Credit;
}
QT_END_NAMESPACE
class Credit : public QWidget {
  Q_OBJECT

 public:
  explicit Credit(QWidget *parent = nullptr);
  ~Credit();

 private slots:
  void on_pushButtonCredit_clicked();

 private:
  Ui::Credit *ui;
};

//}  // namespace s21
#endif  // CREDIT_H
