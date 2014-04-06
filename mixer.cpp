#include <QDebug>
#include <QIcon>
#include <QLabel>
#include <QPushButton>
#include "mixer.h"
#include "ui_mixer.h"
#include "deviceview.h"

Mixer::Mixer(QWidget *parent) :
        QMainWindow(parent),
        ui(new Ui::Mixer),
        mScene(new QGraphicsScene(this)),
		paProxy(new PAProxy("/org/pulseaudio/core1", this))		
{
    ui->setupUi(this);
    ui->graphicsView->setScene(mScene);
    paProxy->setupConnections(this);
}

Mixer::~Mixer()
{
    delete ui;
}

void Mixer::newSink(QDBusObjectPath objectPath)
{
	addDevice(new SinkView(objectPath.path()));
}

void Mixer::newPlaybackStream(QDBusObjectPath objectPath)
{
	addDevice(new PlaybackStreamView(objectPath.path()));
}

void Mixer::newRecordStream(QDBusObjectPath objectPath)
{
	addDevice(new RecordStreamView(objectPath.path()));
}

void Mixer::newSource(QDBusObjectPath objectPath)
{
	addDevice(new SourceView(objectPath.path()));
}


void Mixer::deviceRemoved(QDBusObjectPath objectPath)
{
	DeviceView *deviceView = deviceViews.take(objectPath.path());
	if (deviceView) 
	{
		qDebug() << "Removing" << deviceView->path();
		deviceView->deleteLater();
	}
}

void Mixer::addDevice(DeviceView* deviceView)
{
	if (deviceViews[deviceView->path()])
	{
		qWarning() << "Overwriting device at" << deviceView->path();
		deviceViews[deviceView->path()]->deleteLater();
	}
	qDebug() << "Adding" << deviceView->path();
	deviceViews[deviceView->path()] = deviceView;
	mScene->addWidget(deviceView);
	doLayout();
}


void Mixer::doLayout()
{
	int numdevices[4] = {0,0,0,0};
	int width = 200;
	int height = 100;
	DeviceView *deviceView;
	foreach(deviceView, deviceViews.values())
	{
		int x = numdevices[deviceView->deviceType()]*width;
		int y = deviceView->deviceType()*height;
		deviceView->setGeometry(x, y, 180, 160);
		numdevices[deviceView->deviceType()]++;
	}
}
