#ifndef CREDIT_H
#define CREDIT_H

#include <QWidget>
#include <QMessageBox>

QT_BEGIN_NAMESPACE
namespace Ui {
class Credit;
}
QT_END_NAMESPACE
// namespace s21 {
class Credit : public QWidget {
  Q_OBJECT

 public:
  explicit Credit(QWidget *parent = nullptr);
  ~Credit();

signals:
    void calcCredit(QString& overPayment, QString& allPayment, int month,
                       double summa, QString stavkaProc, QString sumCredit,
                       QString spinBox, size_t comboBox, QString& result);

 private slots:
  void calcClicked();
  
 private:
  Ui::Credit *ui;
};

// }  // namespace s21
#endif  // CREDIT_H
