#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <qdebug.h>

// the constructor
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
	QStringList header;											// the header of the mail list table

    ui->setupUi(this);

	// connect the signals to the slots
    connect(ui->composeButton, SIGNAL(clicked()), this, SLOT(compose()));
    connect(ui->inboxButton, SIGNAL(clicked()), this, SLOT(inbox()));
    connect(ui->sentButton, SIGNAL(clicked()), this, SLOT(sent()));
    connect(ui->draftButton, SIGNAL(clicked()), this, SLOT(draft()));
    connect(ui->backupButton, SIGNAL(clicked()), this, SLOT(backup()));
	connect(ui->junkButton, SIGNAL(clicked()), this, SLOT(junk()));
    connect(ui->settingButton, SIGNAL(clicked()), this, SLOT(setting()));
	connect(ui->updateButton, SIGNAL(clicked()), this, SLOT(updatePwd()));
    connect(ui->loginButton, SIGNAL(clicked()), this, SLOT(login()));
    connect(ui->logoutButton, SIGNAL(clicked()), this, SLOT(logout()));
    connect(ui->registerButton, SIGNAL(clicked()), this, SLOT(registerUser()));
    connect(ui->aboutButton, SIGNAL(clicked()), this, SLOT(about()));
	connect(ui->tableWidget, SIGNAL(cellDoubleClicked(int, int)), this, SLOT(checkMail(int, int)));
	connect(ui->sendButton, SIGNAL(clicked()), this, SLOT(sendMail()));
	connect(ui->cancelButton, SIGNAL(clicked()), this, SLOT(cancelClicked()));
	connect(ui->uploadButton, SIGNAL(clicked()), this, SLOT(upload()));
	connect(ui->delAttButton, SIGNAL(clicked()), this, SLOT(delAtt()));
	connect(ui->downloadButton, SIGNAL(clicked()), this, SLOT(download()));
	connect(ui->deleteButton, SIGNAL(clicked()), this, SLOT(deleteMail()));
	connect(ui->foreverDelButton, SIGNAL(clicked()), this, SLOT(foreverDel()));

	// initialize the mail list table
	ui->tableWidget->setColumnCount(4);
	ui->tableWidget->setSelectionBehavior(QAbstractItemView::SelectRows);
	ui->tableWidget->setEditTriggers(QAbstractItemView::SelectedClicked);
	header << "Tag" << "Sender" << "Date" << "Subject";
	ui->tableWidget->setHorizontalHeaderLabels(header);

    ui->readTextEdit->setReadOnly(true);
	ui->nPwdEdit->setEchoMode(QLineEdit::Password);
	ui->oPwdEdit->setEchoMode(QLineEdit::Password);
	ui->againEdit->setEchoMode(QLineEdit::Password);
	ui->saveButton->hide();
	ui->draftButton->hide();
	ui->backupButton->hide();
	ui->replyButton->hide();
	ui->forwardButton->hide();
	ui->previousButton->hide();
	ui->nextButton->hide();
	ui->welcomeLabel->setText(tr("Welcome!"));					// display the "Welcome" information
    setWindowTitle(tr("QsMail"));								// set the window title

    logined = false;
	for (int i=0;i<Max_buf;i++)
		{
			sendbuf[i]='\0';
			recvbuf[i]='\0';
		}
	mailNum = unReadNum = 0;

    updateInterface(InboxMode);									// turn to the inbox
}

// the destructor
MainWindow::~MainWindow()
{
    delete ui;
}

// update the window interface
void MainWindow::updateInterface(Mode mode){
	QStringList header;

	if(!user.isEmpty())
		refreshList();

	// enable and disable some buttons
    if(logined){
        ui->loginButton->hide();
        ui->registerButton->hide();
        ui->logoutButton->show();

		ui->composeButton->setEnabled(true);
		ui->inboxButton->setEnabled(true);
		ui->sentButton->setEnabled(true);
		ui->junkButton->setEnabled(true);
		ui->settingButton->setEnabled(true);
		ui->deleteButton->setEnabled(true);
		ui->foreverDelButton->setEnabled(true);
    }else{
        ui->loginButton->show();
        ui->registerButton->show();
        ui->logoutButton->hide();

		ui->composeButton->setEnabled(false);
		ui->inboxButton->setEnabled(false);
		ui->sentButton->setEnabled(false);
		ui->junkButton->setEnabled(false);
		ui->settingButton->setEnabled(false);
		ui->deleteButton->setEnabled(false);
		ui->foreverDelButton->setEnabled(false);

		mode = InboxMode;
    }

	/* clear the mail list table, and set the table header. */
	switch(mode){
	case InboxMode:
	case JunkMode:
		ui->tableWidget->clear();
		ui->tableWidget->setRowCount(0);
		header << "Tag" << "Sender" << "Date" << "Subject";
		ui->tableWidget->setHorizontalHeaderLabels(header);
		break;
	case SentMode:
	case DraftMode:
	case BackupMode:
		ui->tableWidget->clear();
		ui->tableWidget->setRowCount(0);
		header << "Tag" << "Recipients" << "Date" << "Subject";
		ui->tableWidget->setHorizontalHeaderLabels(header);
		break;
	}

	// clear the interface information, and display the page
    switch(mode){
    case SentMode:
    case InboxMode:
    case DraftMode:
	case JunkMode:
	case BackupMode:
		attNos.clear();
		attName.clear();
		attNo.clear();
		ui->readTextEdit->clear();
		ui->attachLabel->clear();
		ui->downloadButton->hide();
        ui->pageWidget->setCurrentIndex(0);
        break;

    case ComposeMode:
		attName.clear();
		attNo.clear();
		ui->recipientsEdit->clear();
		ui->subjectEdit->clear();
		ui->writeTextEdit->clear();
		ui->fileNameLabel->clear();
		ui->updateButton->show();
		ui->delAttButton->hide();
        ui->pageWidget->setCurrentIndex(1);
        break;

    case SettingMode:
		ui->oPwdEdit->clear();
		ui->nPwdEdit->clear();
		ui->againEdit->clear();
		ui->pageWidget->setCurrentIndex(2);
        break;
    }
    currentMode = mode;
}

// turn to the compose mode
void MainWindow::compose(){
    updateInterface(ComposeMode);
}

// check the mail information, and send the mail to the server
void MainWindow::sendMail(){
	char buf[Max_buf];

	// check the recipients and subject are not empty
	if(ui->recipientsEdit->text().isEmpty()){
        QMessageBox::information(this, tr("Error"), tr("Recipients can't be empty."));
        return;
    }
	if(ui->subjectEdit->text().isEmpty()){
        QMessageBox::information(this, tr("Error"), tr("Subject can't be empty."));
        return;
    }

	// get the query information
	for (int i=0;i<Max_buf;i++)
		recvbuf[i]='\0';
	sendStr = tr("MAIL\n");
	sendStr.append(ui->recipientsEdit->text());
	sendStr.append(';');
	sendStr.append('\n');
	sendStr.append(user.begin().key());
	sendStr.append('\n');
	sendStr.append(attName + ';' + attNo);
	sendStr.append('\n');
	sendStr.append(ui->subjectEdit->text());
	sendStr.append('\n');
	sendStr.append(ui->writeTextEdit->toPlainText());
	ba = sendStr.toLocal8Bit();
	strcpy_s(sendbuf, ba.data());

	// connect to the server
	cust.ConnectToServer();
	cust.senddata(sendbuf);
	cust.recvdata(recvbuf);

	// handle the receive data
	sscanf(recvbuf, "%s%s", buf, buf);
	buf[4] = '\0';
	if(!strcmp(buf, "FAIL")){
		QMessageBox::information(this, tr("Error"), tr("Send mail failed."));
	}else{
		QMessageBox::information(this, tr("Done"), tr("Send mail Successfully."));
	}

	// fresh the interface
	updateInterface(ComposeMode);
}

// upload the attachment to the server
void MainWindow::upload(){
	QFileDialog dialog(this);

	dialog.setFileMode(QFileDialog::ExistingFile);
	dialog.setViewMode(QFileDialog::Detail);
	dialog.setOptions(QFileDialog::DontUseNativeDialog);
	
	// the the upload file name
	QString fileName = dialog.getOpenFileName();
	if(!fileName.isEmpty()){
		QFile file(fileName);
		// open the file
		if(!file.open(QIODevice::ReadOnly | QIODevice::Unbuffered)){
			QMessageBox::information(this, tr("Error"), tr("Can't open the file."));
			return;
		}

		// copy the data of the file into the query information
		for (int i=0;i<Max_buf;i++)
			recvbuf[i]='\0';
		strcpy_s(sendbuf, "ATTACHMENT\n");
		int i = 11;
		while (!file.atEnd()){
			 file.getChar(&sendbuf[i++]);
		}
		sendbuf[i] = '\0';
		
		// connect to the server
		cust.ConnectToServer();
		cust.senddata(sendbuf);
		cust.recvdata(recvbuf);

		// close the file
		file.close();
		QMessageBox::information(this, tr("Done"), tr("Upload file successfully."));

		// update the interface information, and record the file information
		attNo = tr(recvbuf);
		attName = fileName;
		attName = attName.mid(attName.lastIndexOf(QRegExp("[/\]")) + 1);
		ui->fileNameLabel->setText(attName);
		ui->delAttButton->show();
		ui->uploadButton->hide();
	}
}

// delete the attachment
void MainWindow::delAtt(){
	attName.clear();
	attNo.clear();
	ui->fileNameLabel->clear();
	ui->delAttButton->hide();
	ui->uploadButton->show();
}

// cancel the mail composing
void MainWindow::cancelClicked(){
	updateInterface(ComposeMode);
}

// refresh the mail list
void MainWindow::refreshList(){
	char buf[Max_buf];

	// get the query information
	for (int i=0;i<Max_buf;i++)
		recvbuf[i]='\0';
	sendStr = tr("LOGIN ");
	sendStr.append(user.begin().key());
	sendStr.append(' ');
	sendStr.append(user.begin().value());
	ba = sendStr.toLocal8Bit();
	strcpy_s(sendbuf, ba.data());

	// connect to the server
	cust.ConnectToServer();
	cust.senddata(sendbuf);
	cust.recvdata(recvbuf);

	// handle the receive information
	sscanf(recvbuf, "%s", buf);
	buf[4] = '\0';
	if(!strcmp(buf, "FAIL")){
		QMessageBox::information(this, tr("Error"), tr("Check mail list failed."));
	}else{
		mailList = tr(recvbuf).split("\n");
		mailNum = mailList.size() / 5;
	}
}

// check the inbox mail list
void MainWindow::inbox(){
	int i, j;
	QTableWidgetItem *item;

	// turn to the inbox mode
    updateInterface(InboxMode);
	
	// check the mail in the list
	for(i = 0; i < mailNum; i++)
		if(mailList.at(5*i + 2) == "0" || mailList.at(5*i + 2) == "1"){
			//  insert a new row into the table
			ui->tableWidget->insertRow(0);
			// insert the mail information into the table
			if(mailList.at(5*i + 2).compare(tr("0")) == 0){
				item = new QTableWidgetItem(tr("New"));
				ui->tableWidget->setItem(0, 0, item);
			}
			item = new QTableWidgetItem(mailList.at(5*i + 0));
			ui->tableWidget->setItem(0, 1, item);
			item = new QTableWidgetItem(mailList.at(5*i + 1));
			ui->tableWidget->setItem(0, 2, item);
			item = new QTableWidgetItem(mailList.at(5*i + 4));
			ui->tableWidget->setItem(0, 3, item);
			attNos.prepend(mailList.at(5*i + 3));
		}
}

// check the sent box mail list
void MainWindow::sent(){
	int i, j;
	QTableWidgetItem *item;

	// turn to the sent mode
    updateInterface(SentMode);

	// check the mail in the list
	for(i = 0; i < mailNum; i++)
		if(mailList.at(5*i + 2) == "4"){
			//  insert a new row into the table
			ui->tableWidget->insertRow(0);
			// insert the mail information into the table
			QString str = mailList.at(5*i + 0);
			if(str.endsWith(';'))
				str.remove(str.length()-1, 1);
			item = new QTableWidgetItem(str);
			ui->tableWidget->setItem(0, 1, item);
			item = new QTableWidgetItem(mailList.at(5*i + 1));
			ui->tableWidget->setItem(0, 2, item);
			item = new QTableWidgetItem(mailList.at(5*i + 4));
			ui->tableWidget->setItem(0, 3, item);
			attNos.prepend(mailList.at(5*i + 3));
		}
}

void MainWindow::draft(){
    updateInterface(DraftMode);
}

void MainWindow::backup(){
    updateInterface(BackupMode);
}

// check the junk box mail list
void MainWindow::junk(){
	int i, j;
	QTableWidgetItem *item;

	// turn to the junk mode
    updateInterface(JunkMode);

	// check the mail in the list
	for(i = 0; i < mailNum; i++)
		if(mailList.at(5*i + 2) == "2"){
			// insert a new row into the table
			ui->tableWidget->insertRow(0);
			// insert the mail information into the table
			item = new QTableWidgetItem(mailList.at(5*i + 0));
			ui->tableWidget->setItem(0, 1, item);
			item = new QTableWidgetItem(mailList.at(5*i + 1));
			ui->tableWidget->setItem(0, 2, item);
			item = new QTableWidgetItem(mailList.at(5*i + 4));
			ui->tableWidget->setItem(0, 3, item);
			attNos.prepend(mailList.at(5*i + 3));
		}
}

// check the mail detail information
void MainWindow::checkMail(int row, int column){
	QString str;

	for (int i=0;i<Max_buf;i++)
		recvbuf[i]='\0';
	
	// get the query information
	sendStr = tr("CHECK ");
	if(currentMode == InboxMode){
		sendStr.append("0 ");										// the mail box number
		sendStr.append(user.begin().key());							// the receiver
		sendStr.append(' ');
		sendStr.append(ui->tableWidget->item(row, 1)->text());		// the sender
	}
	else if(currentMode == SentMode){
		sendStr.append("4 ");										// the mail box number
		str = ui->tableWidget->item(row, 1)->text();
		sendStr.append(str.replace(' ', '_'));						// the receiver
		sendStr.append(' ');
		sendStr.append(user.begin().key());							// the sender
	}
	else if(currentMode == JunkMode){
		sendStr.append("2 ");										// the mail box number
		str = ui->tableWidget->item(row, 1)->text();
		if(str.startsWith("To:")){
			str.replace(' ', '_');
			sendStr.append(str);									// the receiver
			sendStr.append(' ');
			sendStr.append(user.begin().key());						// the sender
		}else{
			sendStr.append(user.begin().key());						// the receiver
			sendStr.append(' ');
			sendStr.append(str);									// the sender
		}
	}
	sendStr.append(' ');
	sendStr.append(ui->tableWidget->item(row, 2)->text());
	ba = sendStr.toLocal8Bit();
	strcpy_s(sendbuf, ba.data());

	// connect to the server
	cust.ConnectToServer();
	cust.senddata(sendbuf);
	cust.recvdata(recvbuf);
	
	// display the mail text
	ui->readTextEdit->setText(tr(recvbuf).remove(0, 6));

	// check the attachment
	if(attNos[row] == tr(";")){
		attNo.clear();
		attName.clear();
		ui->attachLabel->setText(tr("No attchments."));
		ui->downloadButton->hide();
	}else{
		attNo = attNos[row].mid(attNos[row].lastIndexOf(';') + 1);
		attName = attNos[row].left(attNos[row].lastIndexOf(';'));
		ui->attachLabel->setText(attName);
		ui->downloadButton->show();
	}
}

// download the attachment
void MainWindow::download(){
	QFileDialog dialog(this);

	dialog.setFileMode(QFileDialog::AnyFile);
	dialog.setViewMode(QFileDialog::Detail);
	dialog.setOptions(QFileDialog::DontUseNativeDialog);
	dialog.setDirectory(dialog.directory().absoluteFilePath(attName));
	
	// get teh save file name
	QString fileName = dialog.getSaveFileName();
	if(!fileName.isEmpty()){
		// get the query information
		for (int i=0;i<Max_buf;i++)
			recvbuf[i]='\0';
		sendStr = tr("DOWNLOAD ");
		sendStr.append(attNo);
		ba = sendStr.toLocal8Bit();
		strcpy_s(sendbuf, ba.data());
		
		// connect to the server
		cust.ConnectToServer();
		cust.senddata(sendbuf);
		cust.recvdata(recvbuf);

		// handle the receive information
		int i = 0;
		while(recvbuf[i] != '\n') i++;
		recvbuf[i] = '\0';
		if(strcmp(recvbuf, "Contents") == 0){
			QFile file(fileName);
			// open an file to store the data
			if(!file.open(QIODevice::WriteOnly | QIODevice::Unbuffered)){
				QMessageBox::information(this, tr("Error"), tr("Can't open the file."));
				return;
			}
			
			// store the received data
			i++;
			while(recvbuf[i] != '\0'){
				file.putChar(recvbuf[i]);
				i++;
			}

			// close the file
			file.close();
			QMessageBox::information(this, tr("Done"), tr("Download file successfully."));
		}else{
			QMessageBox::information(this, tr("Error"), tr("Download file failed."));
		}
	}
}

// delete the mail
void MainWindow::deleteMail(int flag){
	QString str;
	char buf[Max_buf];
	int row = ui->tableWidget->currentRow();

	if(currentMode == JunkMode){
		flag = 1;
	}
	
	// get the query information
	for (int i=0;i<Max_buf;i++)
		recvbuf[i]='\0';
	sendStr = tr("DELETE ");
	sendStr.append(tr("%1").arg(flag));
	sendStr.append(' ');
	sendStr.append(user.begin().key());							// the user
	sendStr.append(' ');
	sendStr.append(tr("%1").arg(currentMode));
	sendStr.append(' ');
	sendStr.append(ui->tableWidget->item(row, 2)->text());
	sendStr.append(' ');
	sendStr.append(attNos[row].mid(attNos[row].lastIndexOf(';') + 1));
	ba = sendStr.toLocal8Bit();
	strcpy_s(sendbuf, ba.data());

	// connect to the server
	cust.ConnectToServer();
	cust.senddata(sendbuf);
	cust.recvdata(recvbuf);

	QMessageBox::information(this, tr("Done"), tr("Delete mail successfully."));

	// update the interface
	switch(currentMode){
	case InboxMode: inbox(); break;
	case SentMode: sent(); break;
	case JunkMode: junk(); break;
	}
}

// delete the mail forever
void MainWindow::foreverDel(){
	deleteMail(1);
}

// turn to the setting page
void MainWindow::setting(){
    updateInterface(SettingMode);
}

// update the user password
void MainWindow::updatePwd(){
	char buf[Max_buf];

	for (int i=0;i<Max_buf;i++)
		recvbuf[i]='\0';

	if(ui->oPwdEdit->text() != user.begin().value()){
		QMessageBox::information(this, tr("Error"), tr("Password error."));
	}else if(ui->nPwdEdit->text() != ui->againEdit->text()){
		QMessageBox::information(this, tr("Error"), tr("Please ensure the passwords are the same."));
	}else{
		// get the query information
		sendStr = tr("MODIFY ");
		sendStr.append(user.begin().key());
		sendStr.append(' ');
		sendStr.append(user.begin().value());
		sendStr.append(' ');
		sendStr.append(ui->nPwdEdit->text());
		sendStr.append(' ');
		sendStr.append(ui->againEdit->text());
		ba = sendStr.toLocal8Bit();
		strcpy_s(sendbuf, ba.data());

		// connect to the server
		cust.ConnectToServer();
		cust.senddata(sendbuf);
		cust.recvdata(recvbuf);

		// handle the receive information
		sscanf(recvbuf, "%s", buf);
		buf[4] = '\0';
		if(!strcmp(buf, "FAIL")){
			QMessageBox::information(this, tr("Error"), tr("Modify password failed."));
		}else{
			user.insert(user.begin().key(), ui->nPwdEdit->text());
			QMessageBox::information(this, tr("Done"), tr("Modify password successfully."));
		}
	}

	// update the interface
	updateInterface(SettingMode);
}

// user login
void MainWindow::login(){
    loginDialog dia;
	char buf[Max_buf];
	
	for (int i=0;i<Max_buf;i++)
		recvbuf[i]='\0';
    if(dia.exec() == QDialog::Accepted){
        user = dia.loginText();
		
		// get the query information
		sendStr = tr("LOGIN ");
		sendStr.append(user.begin().key());
		sendStr.append(' ');
		sendStr.append(user.begin().value());
		ba = sendStr.toLocal8Bit();
		strcpy_s(sendbuf, ba.data());

		// connect to the server
		cust.ConnectToServer();
		cust.senddata(sendbuf);
		cust.recvdata(recvbuf);
		
		// handle the receive information
		sscanf(recvbuf, "%s", buf);
		buf[4] = '\0';
		if(!strcmp(buf, "FAIL")){
			QMessageBox::information(this, tr("Login Error"), tr("User name or password error."));
		}else{
			logined = true;
			ui->welcomeLabel->setText(tr("Welcome \"%1\"!").arg(user.begin().key()));
			inbox();
		}
	}
}

// user logout
void MainWindow::logout(){
    logined = false;
	// clear the user information
	mailNum = unReadNum = 0;
	user.clear();
	mailList.clear();
	ui->welcomeLabel->setText(tr("Welcome!"));

	// turn to the inbox mode
	updateInterface(InboxMode);
}

// register user
void MainWindow::registerUser(){
    RegisterDialog dia;
	char buf[Max_buf];

	if(dia.exec() == QDialog::Accepted){
		user = dia.registerText();

		// get the query information
		sendStr = tr("SIGN_IN ");
		sendStr.append(user.begin().key());
		sendStr.append(' ');
		sendStr.append(user.begin().value());
		ba = sendStr.toLocal8Bit();
		strcpy_s(sendbuf, ba.data());

		// connect to the server
		cust.ConnectToServer();
		cust.senddata(sendbuf);
		cust.recvdata(recvbuf);

		// handle the receive information
		sscanf(recvbuf, "%s%s", buf, buf);
		buf[4] = '\0';
		if(!strcmp(buf, "FAIL")){
			QMessageBox::information(this, tr("Error"), tr("Register failed."));
		}else{
			QMessageBox::information(this, tr("Done"), tr("User \"%1\" registered successfully.").arg(user.begin().key()));
		}
	}
}

// display about window
void MainWindow::about(){
    AboutDialog dia;

    dia.exec();
}
