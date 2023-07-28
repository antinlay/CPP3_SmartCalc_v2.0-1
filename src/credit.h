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
   void showCredit() {this->show();};

signals:
    void uiEventAnnuityCalc(double& S, double& i, size_t n);
    void uiEventDifferentialCalc(double& p, double& o, double S, double i,
                                  size_t n, size_t m);

 private slots:
  void calcClicked();
  
 private:
  Ui::Credit *ui;
};

// }  // namespace s21
#endif  // CREDIT_H
