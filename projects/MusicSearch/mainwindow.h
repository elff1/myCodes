#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTextCodec>
#include <QFileDialog>
#include <QtMultimedia>
#include <QAudioInput>
#include <phonon/phonon>
#include "MusicMatch.h"
#include "musicplay.h"

typedef struct
{
	char fccID[4]; //"RIFF"
	unsigned long dwSize;//length-8
	char fccType[4]; //"WAVE"
}HEADER;
typedef struct
{
	char fccID[4]; //"fmt "
	unsigned long dwSize; //16
	unsigned short wFormatTag; //1
	unsigned short wChannels; //1 or 2
	unsigned long dwSamplesPerSec; //44100
	unsigned long dwAvgBytesPerSec; //
	unsigned short wBlockAlign; //声道数*量化数/8
	unsigned short uiBitsPerSample; //量化数 8 or 16
}FMT;
typedef struct
{
	char fccID[4]; //"data"
	unsigned long dwSize; //length-44
}DATA;

namespace Ui {
    class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
	enum MusicFile {NoFile, SelectedFile, RecordedFile};

public slots:
	void startRecord();
	void stopRecord();
	void tick();
	void selectMusicFile();
	void selectFileChanged();
	void playMusic();
	void searchMusic();

private:
    Ui::MainWindow *ui;
	QStringListModel *listModel;

	MusicFile whichFile;
	QString musicFile;
	QAudioInput* audio;
	QTime t;
	int recording;
	QFile recordFile;
	Phonon::MediaSource source;
	//QByteArray ByteArray;
	MusicMatch matcher;

	void raw2Wav();
};

#endif // MAINWINDOW_H
