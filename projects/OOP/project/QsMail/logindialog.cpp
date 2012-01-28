#include "logindialog.h"
#include "ui_logindialog.h"

loginDialog::loginDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::loginDialog)
{
    ui->setupUi(this);

    connect(ui->userNameEdit, SIGNAL(textChanged(const QString &)),
            this, SLOT(enableLoginButton(const QString &)));
    connect(ui->loginButton, SIGNAL(clicked()),
            this, SLOT(accept()));
    connect(ui->cancelButton, SIGNAL(clicked()),
            this, SLOT(reject()));

	ui->userPwdEdit->setEchoMode(QLineEdit::Password);
    ui->loginButton->setDefault(true);
    ui->loginButton->setEnabled(false);

    setWindowTitle(tr("Login"));
    setFixedSize(sizeHint());
}

loginDialog::~loginDialog()
{
    delete ui;
}

void loginDialog::enableLoginButton(const QString &text){
    ui->loginButton->setEnabled(!text.isEmpty());
}

QMap<QString, QString> loginDialog::loginText(){
    QMap<QString, QString> user;

    user.insert(ui->userNameEdit->text(), ui->userPwdEdit->text());

    return user;
}
