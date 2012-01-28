/*
*	the header of the mainwindow.cpp
*/

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <qtextcodec.h>
#include <QMainWindow>
#include <QMap>
#include <QString>
#include <qstringlist.h>
#include <qmessagebox.h>
#include <QTableWidgetItem>
#include <qfiledialog.h>
#include "logindialog.h"
#include "aboutdialog.h"
#include "registerdialog.h"
#include "client.h"

namespace Ui {
    class MainWindow;
}

class MainWindow : public QMainWindow {
    Q_OBJECT
public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();
    enum Mode { ComposeMode, InboxMode, SentMode, DraftMode, JunkMode, BackupMode, SettingMode };

public slots:
    void compose();								// the compose mail slot
    void inbox();								// the check inbox slot
    void sent();								// the check sent box slot
    void draft();								// the check draft box slot
    void backup();								// the check backup box slot
	void junk();								// the check junk box slot 
    void setting();								// the setting slot
	void updatePwd();							// the modify password slot
    void login();								// the login slot
    void logout();								// the logout slot
    void registerUser();						// the register user slot
    void about();								// the About information slot
	void checkMail(int, int);					// the check mail slot
	void deleteMail(int flag = 0);				// the delete mail slot
	void foreverDel();							// the delete mail forever slot
	void sendMail();							// the send mail slot
	void cancelClicked();						// the cancel compose mail slot
	void upload();								// the upload attachment slot
	void delAtt();								// the delete attachment slot
	void download();							// the download attachment slot

private:
    Ui::MainWindow *ui;

    Mode currentMode;							// the current mail mode
    bool logined;								// the login information
    QMap<QString, QString> user;				// the login user information
	QStringList mailList;						// the mail list of the user
	int mailNum;								// the number of the mails
	int unReadNum;								// the number of unread mails
	QString attName;							// the attachment name
	QString attNo;								// the attachment No.
	QStringList attNos;							// the attachments No. of all the mails in the list

	client cust;
	char sendbuf[Max_buf], recvbuf[Max_buf];	// the send and recerve information
	QString sendStr;
	QByteArray ba;

    void updateInterface(Mode mode);			// update interface
	void refreshList();							// refresh the mail list
};

#endif // MAINWINDOW_H
