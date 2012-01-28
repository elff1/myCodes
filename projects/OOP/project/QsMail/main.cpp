#include <QtGui/QApplication>
#include "mainwindow.h"
#define Max_buf 10240

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
	
	QTextCodec::setCodecForTr(QTextCodec::codecForName("GB2312"));
    MainWindow w;
    w.show();
    return a.exec();
}
