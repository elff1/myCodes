#include <QtGui/QApplication>
#include "mainwindow.h"

int main(int argc, char *argv[])
{
	freopen("out.txt","w",stdout);

    QApplication a(argc, argv);
	//QTextCodec::setCodecForTr(QTextCodec::codecForName("gb18030"));
	QTextCodec *codec = QTextCodec::codecForName("System");    //获取系统编码
	QTextCodec::setCodecForLocale(codec);
	QTextCodec::setCodecForCStrings(codec);
	QTextCodec::setCodecForTr(codec);

    MainWindow w;
    w.show();

    return a.exec();

	fclose(stdout);
}
