#include <QIcon>
#include <QPixmap>
#include <QDebug>
#include <QMessageBox>
#include <math.h>

#include "deviceview.h"
#include "ui_deviceview.h"
#include "paproxy.h"

DeviceView::DeviceView(DeviceType deviceType, QString path, QWidget *parent): 
	QWidget(parent), 
	ui(new Ui::DeviceView), 
	mDeviceType(deviceType),
	mPath(path)
{
	ui->setupUi(this);
   
	/* tbr ------------------- */
	ui->appNameLabel->setText(path);

    qDebug() << "ui->pushButton" << ui->pushButton;
    connect(ui->pushButton, SIGNAL(clicked()), this, SLOT(settings()));
}

DeviceView::~DeviceView()
{
    delete ui;
}

void DeviceView::settings()
{
    QMessageBox messageBox;
    messageBox.setText(ui->appNameLabel->text());
    messageBox.setInformativeText("Settings... (tbd)");
    messageBox.exec();
}

void DeviceView::setIcon(QString iconName)
{
    QIcon icon = QIcon::fromTheme(iconName);
    QPixmap pixmap = icon.pixmap(24,24);
    ui->iconLabel->setPixmap(icon.pixmap(24, 24));
}



SinkView::SinkView(QString path, QWidget *parent) : DeviceView(SINK, path, parent)
{
    setIcon("audio-speakers");
    m_Sink = new Sink(path, this);
}
 
SinkView::~SinkView()
{
}

SourceView::SourceView(QString path, QWidget *parent) : DeviceView(SOURCE, path, parent)
{
	setIcon("audio-input-microphone");
}
 
SourceView::~SourceView()
{
}

PlaybackStreamView::PlaybackStreamView(QString path, QWidget *parent) : DeviceView(PLAYBACKSTREAM, path, parent)
{
	setIcon("application-x-executable");
}
 
PlaybackStreamView::~PlaybackStreamView()
{
}

RecordStreamView::RecordStreamView(QString path, QWidget *parent) : DeviceView(RECORDSTREAM, path, parent)
{
	setIcon("application-x-executable");
}
 
RecordStreamView::~RecordStreamView()
{
}
