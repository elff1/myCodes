#include <QMessageBox>
#include "registerdialog.h"
#include "ui_registerdialog.h"

RegisterDialog::RegisterDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::RegisterDialog)
{
    ui->setupUi(this);

    connect(ui->buttonBox, SIGNAL(accepted()), this, SLOT(okClicked()));
    connect(ui->buttonBox, SIGNAL(rejected()), this, SLOT(reject()));

	ui->passwordEdit->setEchoMode(QLineEdit::Password);
	ui->againEdit->setEchoMode(QLineEdit::Password);
    setWindowTitle(tr("Register"));
    setFixedSize(sizeHint());
}

RegisterDialog::~RegisterDialog()
{
    delete ui;
}

void RegisterDialog::okClicked(){
    name = ui->nameEdit->text();
    pwd = ui->passwordEdit->text();
    again = ui->againEdit->text();


    if(name.isEmpty()){
        QMessageBox::information(this, tr("Empty Field"), tr("Please enter a name."));
        return;
    }else if(pwd != again){
        QMessageBox::information(this, tr("Error"),
                                 tr("Please ensure the passwords are the same."));
		return;
    }
    accept();
}

QMap<QString, QString> RegisterDialog::registerText(){
    QMap<QString, QString> user;

    user.insert(ui->nameEdit->text(), ui->passwordEdit->text());

    return user;
}