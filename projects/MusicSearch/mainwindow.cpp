#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
	ui->setupUi(this);

	QPalette palette;
	palette.setBrush(QPalette::Light, Qt::darkGray);
	ui->recordNumber->setPalette(palette);

	QTimer *timer = new QTimer(this);

	connect(ui->searchButton, SIGNAL(clicked()), this, SLOT(searchMusic()));
	connect(ui->recordButton, SIGNAL(clicked()), this, SLOT(startRecord()));
	connect(ui->stopButton, SIGNAL(clicked()), this, SLOT(stopRecord()));
	connect(timer, SIGNAL(timeout()), this, SLOT(tick()));
	connect(ui->browseButton, SIGNAL(clicked()), this, SLOT(selectMusicFile()));
	connect(ui->fileEdit, SIGNAL(textEdited(QString)), this, SLOT(selectFileChanged()));
	connect(ui->playButton, SIGNAL(clicked()), this, SLOT(playMusic()));

	whichFile = NoFile;
	matcher.initialize();
	listModel = new QStringListModel();
	ui->resultView->setModel(listModel);
	ui->recordNumber->display("00:00");
	ui->recordNumber->hide();
	ui->playButton->hide();
	ui->searchMusicButton->hide();
	ui->addMusicButton->hide();
	timer->start(1000);
	recording = 0;
	
	setWindowTitle(tr("Music Searching"));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::searchMusic() {
	if (whichFile == NoFile)
		return;

	//cout << musicFile.toStdString();
	string result[SHOW_NUM];
	int resNum;
	if(matcher.match(musicFile.toStdString(), result, &resNum)) {
		//ui->searchMusicNameEdit->setText(tr(result[0].c_str()));
		QStringList list;
		cout<<"resnum:"<<resNum<<endl;
		for(int i = 0; i < resNum; i++)
			list.append(result[i].c_str());
			//cout << result[i] << endl;

		//listModel = new QStringListModel(list);
		listModel->setStringList(list);
	}
}

void MainWindow::startRecord() {
	recordFile.setFileName("record.raw");
	recordFile.open( QIODevice::WriteOnly | QIODevice::Truncate );

	QAudioFormat format;
	// set up the format you want, eg.
	format.setFrequency(8000);
	format.setChannels(1);
	format.setSampleSize(8);
	format.setCodec("audio/pcm");
	format.setByteOrder(QAudioFormat::LittleEndian);
	format.setSampleType(QAudioFormat::UnSignedInt);

	QAudioDeviceInfo info = QAudioDeviceInfo::defaultInputDevice();
	if (!info.isFormatSupported(format)) {
		qWarning()<<"default format not supported try to use nearest";
		format = info.nearestFormat(format);
	}

	audio = new QAudioInput(format, this);
	QTimer::singleShot(3000, this, SLOT(stopRecording()));
	audio->start(&recordFile);
// Records audio for 3000ms
	t.start();
	recording = 1;
}

void MainWindow::stopRecord() {
	if(!recording)
		return ;

	t.elapsed();
	
	audio->stop();
	recordFile.close();
	delete audio;
	raw2Wav();

	ui->fileEdit->clear();
	whichFile = RecordedFile;
	musicFile = QString("record.wav");
	recording = 0;
}

void MainWindow::selectMusicFile()
{
	QString file = QFileDialog::getOpenFileName(this, tr("Select Music File"));
	if(file.isEmpty())
		return;

	ui->fileEdit->setText(file);
	whichFile = SelectedFile;
	musicFile = file;

//	QFile *myfile = new QFile(file);
//	myfile->open(QIODevice::ReadWrite);
//	ByteArray = myfile->readAll();
}

void MainWindow::selectFileChanged() {
	if(ui->fileEdit->text().isEmpty()) {
		whichFile = NoFile;
		musicFile.clear();
	}
	else {
		whichFile = SelectedFile;
		musicFile = ui->fileEdit->text();
	}
}

void MainWindow::playMusic() {
	if (whichFile == NoFile)
		return;

	source = Phonon::MediaSource(musicFile);
	if(source.type() == Phonon::MediaSource::Empty)
		return;

	MusicPlayer musicPlayer(source);
	musicPlayer.exec();

//	if(ByteArray.isEmpty())
//		return;
//	Phonon::MediaObject* player = Phonon::createPlayer( Phonon::MusicCategory );
//	QBuffer* soundData = new QBuffer( player );
//	soundData->setData( ByteArray );
//	player->setCurrentSource( soundData );
//	player->setParent( this );
//	player->play();
//	ByteArray.clear();
}

void MainWindow::tick()
{
	ui->recordNumber->display(t.toString("mm:ss"));
}

void MainWindow::raw2Wav() {
	HEADER pcmHEADER;
	FMT pcmFMT;
	DATA pcmDATA;
	unsigned long m_pcmData;
	FILE *fp, *fpCopy;
	fp = fopen("record.raw", "rb");
	fpCopy = fopen("record.wav", "wb+");
	if(!fp)
	{
		qDebug() << "open pcm file error";
		return;
	}
	if(!fpCopy)
	{
		qDebug() << "create wave file error";
		return;
	}
	qstrcpy(pcmHEADER.fccID, "RIFF");
	qstrcpy(pcmHEADER.fccType, "WAVE");
	fseek(fpCopy, sizeof(HEADER), 1);
	pcmFMT.dwSamplesPerSec = 8000;
	pcmFMT.dwAvgBytesPerSec = pcmFMT.dwSamplesPerSec*sizeof(m_pcmData);
	pcmFMT.uiBitsPerSample = 8;
	qstrcpy(pcmFMT.fccID, "fmt ");
	pcmFMT.dwSize = 16;
	pcmFMT.wBlockAlign = 1;
	pcmFMT.wChannels = 1;
	pcmFMT.wFormatTag = 1;
	fwrite(&pcmFMT, sizeof(FMT), 1, fpCopy);
	qstrcpy(pcmDATA.fccID, "data");
	pcmDATA.dwSize = 0;
	fseek(fpCopy, sizeof(DATA), 1);
	fread(&m_pcmData, sizeof(unsigned long), 1, fp);
	while(!feof(fp))
	{
		pcmDATA.dwSize += 4; //计算数据的长度；每读入一个数据，长度就加一；
		fwrite(&m_pcmData, sizeof(unsigned long), 1, fpCopy); //将数据写入.wav文件;
		fread(&m_pcmData, sizeof(unsigned long), 1, fp); //从.pcm中读入数据
	}
	fclose(fp);
	pcmHEADER.dwSize = 44+pcmDATA.dwSize-8; //根据pcmDATA.dwsize得出pcmHEADER.dwsize的值
	rewind(fpCopy); //将fpCpy变为.wav的头，以便于写入HEADER和DATA;
	fwrite(&pcmHEADER, sizeof(HEADER), 1, fpCopy); //写入HEADER
	fseek(fpCopy, sizeof(FMT), 1);  //跳过FMT,因为FMT已经写入
	fwrite(&pcmDATA, sizeof(DATA), 1, fpCopy);   //写入DATA;
	fclose(fpCopy);

	cout << "dwSize: " << pcmDATA.dwSize << endl;
}
