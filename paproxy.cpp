#include <QString>
#include <QDBusConnection>
#include <QDBusInterface>
#include <QDBusReply>
#include <QDBusMessage>
#include <QString>
#include <QDebug>
#include <QMap>
#include <QByteArray>
#include <QDBusMetaType>

#include "mixer.h"
#include "paproxy.h"
#include "device_proxy.h"

PAProxy::PAProxy(QString path, QObject *parent) :
	PAO(path, parent)
{
    m_org_PulseAudio_Core1 = createInterface("org.PulseAudio.Core1");
}


PAProxy::~PAProxy()
{
}

void PAProxy::setupConnections(Mixer *mixer)
{
	qDebug() << "Declare interest...";
	QVariant v;
	v.setValue<QList<QDBusObjectPath> >((QList<QDBusObjectPath>() << QDBusObjectPath(path())));
	QVariant::fromValue(QList<QDBusObjectPath>() << QDBusObjectPath(path()));
	QDBusMessage reply = m_org_PulseAudio_Core1->call("ListenForSignal", 
													  "", 
													  QVariant::fromValue(QList<QDBusObjectPath>()));
	qDebug() << "Listen for signal reply:"	 << reply;

	qDebug() << "Connecting...";
	connect(m_org_PulseAudio_Core1, SIGNAL(NewSink(QDBusObjectPath)), mixer, SLOT(newSink(QDBusObjectPath)));
	connect(m_org_PulseAudio_Core1, SIGNAL(NewSource(QDBusObjectPath)), mixer, SLOT(newSource(QDBusObjectPath)));
	connect(m_org_PulseAudio_Core1, SIGNAL(NewPlaybackStream(QDBusObjectPath)), mixer, SLOT(newPlaybackStream(QDBusObjectPath)));
	connect(m_org_PulseAudio_Core1, SIGNAL(NewRecordStream(QDBusObjectPath)), mixer, SLOT(newRecordStream(QDBusObjectPath)));
	connect(m_org_PulseAudio_Core1, SIGNAL(SinkRemoved(QDBusObjectPath)), mixer, SLOT(deviceRemoved(QDBusObjectPath)));
	connect(m_org_PulseAudio_Core1, SIGNAL(SourceRemoved(QDBusObjectPath)), mixer, SLOT(deviceRemoved(QDBusObjectPath)));
	connect(m_org_PulseAudio_Core1, SIGNAL(PlaybackStreamRemoved(QDBusObjectPath)), mixer, SLOT(deviceRemoved(QDBusObjectPath)));
	connect(m_org_PulseAudio_Core1, SIGNAL(RecordStreamRemoved(QDBusObjectPath)), mixer, SLOT(deviceRemoved(QDBusObjectPath)));


	qDebug() << "Calling mixer slots..";
	QDBusObjectPath objectPath; 

	
	QList<QDBusObjectPath> sinks = getProperty<QList<QDBusObjectPath> >("Sinks", m_org_PulseAudio_Core1);
	foreach (objectPath, sinks) { qDebug() << "sink" << objectPath.path(); mixer->newSink(objectPath);}

	QList<QDBusObjectPath> sources = getProperty<QList<QDBusObjectPath> >("Sources", m_org_PulseAudio_Core1);
	foreach (objectPath, sources) { qDebug() << "source" << objectPath.path(); mixer->newSource(objectPath);}

	QList<QDBusObjectPath> inputStreams = getProperty<QList<QDBusObjectPath> >("RecordStreamss", m_org_PulseAudio_Core1);
	foreach (objectPath, inputStreams) { qDebug() << "recordStream" << objectPath.path(); mixer->newRecordStream(objectPath);}

	QList<QDBusObjectPath> outputStreams = getProperty<QList<QDBusObjectPath> >("PlaybackStreams", m_org_PulseAudio_Core1);
	foreach (objectPath, outputStreams) { qDebug() << "playbackStream" << objectPath.path(); mixer->newPlaybackStream(objectPath);}

	qDebug() << "Setup done";
}

Sink::Sink(QString path, QObject *parent) : PAO(path, parent)
{
    m_org_PulseAudio_Core1_Sink = createInterface("org.PulseAudio.Core1.Device");
    OrgPulseAudioCore1DeviceInterface *deviceProxy = new OrgPulseAudioCore1DeviceInterface(QString(), path, connection(), this);
    DBusPropertyList props = deviceProxy->propertyList();
    qDebug() << "props: " << props.keys();
    QString propName;
    foreach (propName, props.keys()) {
        qDebug() << propName << "-->" << props[propName];
    }
}

Sink::~Sink()
{
}

Source::Source(QString path, QObject *parent) : PAO(path, parent)
{
}

Source::~Source()
{
}

InputStream::InputStream(QString path, QObject *parent) : PAO(path, parent)
{
}

InputStream::~InputStream()
{
}

OutputStream::OutputStream(QString path, QObject *parent) : PAO(path, parent)
{
}

OutputStream::~OutputStream()
{
}






