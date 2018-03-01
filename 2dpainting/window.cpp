/****************************************************************************
**
** Copyright (C) 2013 Digia Plc and/or its subsidiary(-ies).
** Contact: http://www.qt-project.org/legal
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
**   * Neither the name of Digia Plc and its Subsidiary(-ies) nor the names
**     of its contributors may be used to endorse or promote products derived
**     from this software without specific prior written permission.
**
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
**
** $QT_END_LICENSE$
**
****************************************************************************/
#pragma execution_character_set("utf-8")
#include "glwidget.h"
#include "window.h"

#include <QGridLayout>
#include <QLabel>
#include <QTimer>
#include <qspinbox.h>
#include <qdatetimeedit.h>
#include <qpushbutton.h>

//! [0]
QTimer *timer;
bool running = true;
QSpinBox *AddSpin;
float addin = 1.0;
GLWidget *openGL;
QDateTimeEdit *datetime;
QDateTime lasttime;
QDateTime nowtime;
bool viewflag = true;
bool first;
QSpinBox *jingduSpin, *weiduSpin;
Window::Window()
{
    setWindowTitle(tr("9 Plant"));
	setMinimumSize(1400, 1000);

	openGL = new GLWidget(this);
    QLabel *openGLLabel = new QLabel(tr("9 Plant Running"));
    openGLLabel->setAlignment(Qt::AlignHCenter);

    QGridLayout *layout = new QGridLayout;
    layout->addWidget(openGL, 0, 1);
    layout->addWidget(openGLLabel, 1, 1);

	QVBoxLayout *verticalLayout = new  QVBoxLayout;
	verticalLayout->setSpacing(6);
	layout->addLayout(verticalLayout, 0, 2);

	QHBoxLayout *Addlayout = new QHBoxLayout;
	QLabel *AddLabel = new QLabel;
	AddLabel->setText("加速比");
	AddSpin = new QSpinBox;
	AddSpin->setMinimum(-1440);
	AddSpin->setMaximum(3650);
	Addlayout->addWidget(AddLabel);
	Addlayout->addWidget(AddSpin);
	verticalLayout->addLayout(Addlayout);

	datetime = new QDateTimeEdit;
	datetime->setDateTime(QDateTime(QDate(2017, 12, 11), QTime(0, 0, 0)));
	verticalLayout->addWidget(datetime);

	QPushButton *start = new QPushButton;
	start->setText("开始/暂停");
	verticalLayout->addWidget(start);

	QPushButton *camera = new QPushButton;
	camera->setText("太空/地球");
	verticalLayout->addWidget(camera);


	timer = new QTimer(this);
	openGL->setaddin(addin);
	connect(timer, SIGNAL(timeout()), openGL, SLOT(animate()));
	connect(timer, SIGNAL(timeout()), this, SLOT(timeupdate()));
	timer->start(1);

	QHBoxLayout *jingdulayout = new QHBoxLayout;
	QLabel *jingduLable = new QLabel;
	jingduLable->setText("经度");
	jingduSpin = new QSpinBox;
	jingduSpin->setMinimum(-180);
	jingduSpin->setMaximum(180);
	jingdulayout->addWidget(jingduLable);
	jingdulayout->addWidget(jingduSpin);
	verticalLayout->addLayout(jingdulayout);

	QHBoxLayout *weidulayout = new QHBoxLayout;
	QLabel *weiduLabel = new QLabel;
	weiduLabel->setText("维度");
    weiduSpin = new QSpinBox;
	weiduSpin->setMinimum(-90);
	weiduSpin->setMaximum(90);
	weidulayout->addWidget(weiduLabel);
	weidulayout->addWidget(weiduSpin);
	verticalLayout->addLayout(weidulayout);


	connect(start, SIGNAL(clicked()), this, SLOT(restart()));
    setLayout(layout);

	connect(AddSpin, SIGNAL(valueChanged(int)), this, SLOT(addchange(int)));

	connect(camera,SIGNAL(clicked()),this,SLOT(changeView()));

}


void Window::restart()
{

	if (running)
	{
		timer->stop();	
		openGL->setaddin(0);
		lasttime = datetime->dateTime();
	}
	else
	{
		openGL->setjingweidu(weiduSpin->value(),jingduSpin->value());
		nowtime = datetime->dateTime();
		if (lasttime != nowtime)
		{			
			int seconds = lasttime.secsTo(nowtime);
			cout << "不相等";
			openGL->fastToDay(seconds*1.0/24/3600);
			first = false;
			//Sleep(2);
		}
		timer->start();
		openGL->setaddin(addin);
		
	}
	running=!running;
	
}

void Window::addchange(int)
{
	int value = AddSpin->value();
	if (value > 1)
		addin = 1 * value;
	else if (value < -1)
		addin = 1.0 / abs(value);
	else
		addin = 1;
	openGL->setaddin(addin);
	//int b = value;
}

void Window::timeupdate()
{
	//计算多少分总
	QDateTime currenttime = datetime->dateTime();
	QDateTime nexttime=currenttime.addSecs(1*addin*24*3600);
	datetime->setDateTime(nexttime);
	//if (first)
	//	openGL->setaddin(addin);
	//else
	//	first = !first;
	//openGL->setaddin(addin);
}

void Window::changeView()
{
	viewflag = !viewflag;
	openGL->setViewFlag(viewflag);
}
