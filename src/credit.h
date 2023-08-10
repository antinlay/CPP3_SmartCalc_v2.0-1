#ifndef CREDIT_H
#define CREDIT_H

#include <QtWidgets/QMessageBox>

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
  void showCredit() {
    this->show();
    emit uiEventSendUi(ui);
  };

 signals:
  void uiEventOutputInfo(QString& anuInfo, QString& payment,
                         QString& overpayment);
  void uiEventSendUi(Ui::Credit* r);

 private slots:
  void calcClicked();

 private:
  Ui::Credit* ui = nullptr;
};

#endif  // CREDIT_H
