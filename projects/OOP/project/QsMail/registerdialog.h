#ifndef REGISTERDIALOG_H
#define REGISTERDIALOG_H

#include <QDialog>
#include <QString>

namespace Ui {
    class RegisterDialog;
}

class RegisterDialog : public QDialog {
    Q_OBJECT
public:
    RegisterDialog(QWidget *parent = 0);
    ~RegisterDialog();
	QMap<QString, QString> registerText();

public slots:
    void okClicked();

private:
    Ui::RegisterDialog *ui;

    QString name;
    QString pwd;
    QString again;
};

#endif // REGISTERDIALOG_H
