/****************************************************************************
**
** Copyright (C) 2011 Nokia Corporation and/or its subsidiary(-ies).
** All rights reserved.
** Contact: Nokia Corporation (qt-info@nokia.com)
**
** This file is part of the examples of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:BSD$
** You may use this file under the terms of the BSD license as follows:
**
** "Redistribution and use in source and binary forms, with or without
** modification, are permitted provided that the following conditions are
** met:
**   * Redistributions of source code must retain the above copyright
**     notice, this list of conditions and the following disclaimer.
**   * Redistributions in binary form must reproduce the above copyright
**     notice, this list of conditions and the following disclaimer in
**     the documentation and/or other materials provided with the
**     distribution.
**   * Neither the name of Nokia Corporation and its Subsidiary(-ies) nor
**     the names of its contributors may be used to endorse or promote
**     products derived from this software without specific prior written
**     permission.
**
** THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
** "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
** LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
** A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
** OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
** SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
** LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
** DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
** THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
** (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
** OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE."
** $QT_END_LICENSE$
**
***************************************************************************/

#include <QtGui>

#include "musicplay.h"

MusicPlayer::MusicPlayer(Phonon::MediaSource source, QWidget *parent) :
	QDialog(parent)
{
    audioOutput = new Phonon::AudioOutput(Phonon::MusicCategory, this);
	mediaObject = new Phonon::MediaObject(this);

	mediaObject->setTickInterval(1000);

    connect(mediaObject, SIGNAL(tick(qint64)), this, SLOT(tick(qint64)));
    connect(mediaObject, SIGNAL(stateChanged(Phonon::State,Phonon::State)),
			this, SLOT(stateChanged(Phonon::State,Phonon::State)));

	Phonon::createPath(mediaObject, audioOutput);

	setupActions();
    setupUi();
    timeLcd->display("00:00"); 
	mediaObject->setCurrentSource(source);
}

void MusicPlayer::stateChanged(Phonon::State newState, Phonon::State /* oldState */)
{
    switch (newState) {
        case Phonon::ErrorState:
            if (mediaObject->errorType() == Phonon::FatalError) {
                QMessageBox::warning(this, tr("Fatal Error"),
                mediaObject->errorString());
            } else {
                QMessageBox::warning(this, tr("Error"),
                mediaObject->errorString());
            }
			break;

        case Phonon::PlayingState:
                playAction->setEnabled(false);
                pauseAction->setEnabled(true);
                stopAction->setEnabled(true);
                break;
        case Phonon::StoppedState:
                stopAction->setEnabled(false);
                playAction->setEnabled(true);
                pauseAction->setEnabled(false);
                timeLcd->display("00:00");
                break;
        case Phonon::PausedState:
                pauseAction->setEnabled(false);
                stopAction->setEnabled(true);
                playAction->setEnabled(true);
				break;

        case Phonon::BufferingState:
                break;
        default:
            ;
    }
}

void MusicPlayer::tick(qint64 time)
{
	QTime displayTime(0, (time / 60000) % 60, (time / 1000) % 60);

    timeLcd->display(displayTime.toString("mm:ss"));
}

void MusicPlayer::setupActions()
{
	playAction = new QAction(style()->standardIcon(QStyle::SP_MediaPlay), tr("Play"), this);
	playAction->setShortcut(tr("Ctrl+P"));
	playAction->setEnabled(true);
	pauseAction = new QAction(style()->standardIcon(QStyle::SP_MediaPause), tr("Pause"), this);
	pauseAction->setShortcut(tr("Ctrl+A"));
	pauseAction->setDisabled(true);
	stopAction = new QAction(style()->standardIcon(QStyle::SP_MediaStop), tr("Stop"), this);
	stopAction->setShortcut(tr("Ctrl+S"));
	stopAction->setDisabled(true);
	exitAction = new QAction(tr("E&xit"), this);
	exitAction->setShortcuts(QKeySequence::Quit);

	connect(playAction, SIGNAL(triggered()), mediaObject, SLOT(play()));
	connect(pauseAction, SIGNAL(triggered()), mediaObject, SLOT(pause()) );
	connect(stopAction, SIGNAL(triggered()), mediaObject, SLOT(stop()));

	connect(exitAction, SIGNAL(triggered()), this, SLOT(close()));
}

void MusicPlayer::setupUi()
{
	QToolBar *bar = new QToolBar;

	bar->addAction(playAction);
	bar->addAction(pauseAction);
	bar->addAction(stopAction);

	seekSlider = new Phonon::SeekSlider(this);
	seekSlider->setMediaObject(mediaObject);

	volumeSlider = new Phonon::VolumeSlider(this);
	volumeSlider->setAudioOutput(audioOutput);
	volumeSlider->setSizePolicy(QSizePolicy::Maximum, QSizePolicy::Maximum);

	QLabel *volumeLabel = new QLabel;
	volumeLabel->setPixmap(QPixmap("images/volume.png"));

	QPalette palette;
	palette.setBrush(QPalette::Light, Qt::darkGray);

	timeLcd = new QLCDNumber;
	timeLcd->setPalette(palette);

	QHBoxLayout *seekerLayout = new QHBoxLayout;
	seekerLayout->addWidget(seekSlider);
	seekerLayout->addWidget(timeLcd);

	QHBoxLayout *playbackLayout = new QHBoxLayout;
	playbackLayout->addWidget(bar);
	playbackLayout->addStretch();
	playbackLayout->addWidget(volumeLabel);
	playbackLayout->addWidget(volumeSlider);

	QVBoxLayout *mainLayout = new QVBoxLayout;
	mainLayout->addLayout(seekerLayout);
	mainLayout->addLayout(playbackLayout);

	//QWidget *widget = new QWidget;
	//QDialog *widget = new QDialog;
	//widget->setLayout(mainLayout);

//	setCentralWidget(widget);
	setLayout(mainLayout);
	setWindowTitle("Music Player");
	//widget->show();
}
