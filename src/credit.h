#ifndef CREDIT_H
#define CREDIT_H

#include <QDate>
#include <QMessageBox>

#include "ui_credit.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class Credit;
}
QT_END_NAMESPACE

class Credit : public QWidget {
  Q_OBJECT

 public:
  explicit Credit(QWidget* parent = nullptr);
  ~Credit();
  void showCredit() { this->show(); };

 signals:
  void uiEventOutputInfo(int caseIndex, double& S, double& i, QDate currentDate,
                         size_t n, QString& anuInfo);

 private slots:
  void calcClicked();

 private:
  Ui::Credit* ui;
};

#endif  // CREDIT_H
