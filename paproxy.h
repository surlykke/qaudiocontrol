#ifndef PAPROXY_H
#define PAPROXY_H

#include <QObject>
#include <QDBusInterface>
#include <QDBusArgument>
#include <QDebug>
#include <QList>
#include <QMap>

class Mixer;



// CRTP
class PAO : public QObject
{

public:
    PAO(QString path, QObject *parent = 0) : QObject(parent), mPath(path)
    {
    }


protected:
    QDBusInterface* createInterface(QString interfaceName)
    {
        return new QDBusInterface(QString(), mPath, interfaceName, connection(), this);
    }

    template<typename PropertyType> PropertyType getProperty(const char* propertyName, QDBusInterface *interface)
    {
        QVariant variant = interface->property(propertyName);
        return variant.value<PropertyType>();
    }

    QString path() { return mPath; }

    static QDBusConnection& connection()
    {
        static QDBusConnection * conn = 0;
        if (!conn)
        {
            QDBusInterface interface("org.PulseAudio1", "/org/pulseaudio/server_lookup1", "org.PulseAudio.ServerLookup1");
            QVariant var = interface.property("Address");
            conn = new QDBusConnection(QDBusConnection::connectToPeer(var.toString(), "pulseAudioConnection"));
        }
        return *conn;
    }

private:


    QString mPath;
};

class PAProxy : public PAO
{
    Q_OBJECT

public:
    PAProxy(QString path, QObject *parent = 0);
    virtual ~PAProxy();
	
	void setupConnections(Mixer* mixer);

signals:
    void sinkAppeared(QDBusObjectPath objectPath);
    void sinkDisappeared(QDBusObjectPath objectPath);
	
	void sourceAppeared(QDBusObjectPath objectPath);
	void sourceDisappeared(QDBusObjectPath objectPath);

	void inputStreamAppeared(QDBusObjectPath objectPath);
	void inputStreamDisappeared(QDBusObjectPath objectPath);

	void outputStreamAppeared(QDBusObjectPath objectPath);
	void outputStreamDisappeared(QDBusObjectPath objectPath);

private:
    QDBusInterface *m_org_PulseAudio_Core1;
};

class Sink : public PAO
{
public:
    Sink(QString path, QObject *parent = 0);
    virtual ~Sink();
private:
    QDBusInterface *m_org_PulseAudio_Core1_Sink;
};

class Source : public PAO
{
public:
    Source(QString path, QObject *parent = 0);
    virtual ~Source();
};

class InputStream : public PAO
{
public:
    InputStream(QString path, QObject *parent = 0);
    virtual ~InputStream();
};

class OutputStream : public PAO
{
public:
    OutputStream(QString path, QObject *parent = 0);
    virtual ~OutputStream();
};


#endif // PAPROXY_H
