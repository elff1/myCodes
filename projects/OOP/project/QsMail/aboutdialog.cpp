#include "aboutdialog.h"
#include "ui_aboutdialog.h"

AboutDialog::AboutDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AboutDialog)
{
    ui->setupUi(this);

    //connect(ui->okButton, SIGNAL(clicked()), this, SLOT(close()));

    setWindowTitle(tr("About Us"));
    setFixedSize(sizeHint());
}

AboutDialog::~AboutDialog()
{
    delete ui;
}
