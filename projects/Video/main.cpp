#include <iostream>
#include <QtCore/QCoreApplication>
#include <QImage>
#include <QColor>

using namespace std;

#define FileNum 601
#define Threshold1 1000000
#define Threshold21 100
#define Threshold22 10000

int main(int argc, char *argv[])
{
	QCoreApplication a(argc, argv);

	QImage p, q;
	QString pre = "pic/Bravia.Advert-avi-000";
	QString mid;
	QString post = ".bmp";
	QString pName;

	int height, width;
	int i, j, k;
	int light[FileNum + 5];
	int diffPix;
	bool priFlag;

	light[0] = 0;
	for(k = 1; k <= FileNum; k++) {
		light[k] = 0;
		diffPix = 0;
		priFlag = false;
		
		mid.setNum(k);
		pName = pre + mid + post;

		p.load(pName);
		height = p.height();
		width = p.width();

		for(i = 0; i < height; i++) {
			for(j = 0; j < width; j++) {
				light[k] += QColor(p.pixel(j, i)).lightness();

				if(k == 1)
					diffPix++;
				else
					if(abs(QColor(p.pixel(j, i)).black() - QColor(q.pixel(j, i)).black()) > Threshold21)
						diffPix++;
			}
		}
		if(abs(light[k] - light[k-1]) > Threshold1) {
			cout << "1: " << k << ' ';
			priFlag = true;
		}

		if(diffPix > Threshold22) {
			cout << "2: " << k << ' ';
			priFlag = true;
		}

		if(priFlag)
			cout << endl;
		q = p;
	}

	return a.exec();
}
