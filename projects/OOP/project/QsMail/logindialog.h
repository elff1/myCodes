#ifndef LOGINDIALOG_H
#define LOGINDIALOG_H

#include <QDialog>
#include <QMap>
//#include "client.h"

namespace Ui {
    class loginDialog;
}

class loginDialog : public QDialog {
    Q_OBJECT
public:
    loginDialog(QWidget *parent = 0);
    ~loginDialog();
    QMap<QString, QString> loginText();

private slots:
    void enableLoginButton(const QString &);

private:
    Ui::loginDialog *ui;
};

#endif // LOGINDIALOG_H
