#ifndef UNIT2_H
#define UNIT2_H

#include <QWidget>
#include <QString>

namespace Ui {
class DeviceView;
}

enum DeviceType 
{
	SINK,
	PLAYBACKSTREAM,
	RECORDSTREAM,
	SOURCE
};

class Sink;

class DeviceView : public QWidget
{
    Q_OBJECT
    
public:

    explicit DeviceView(DeviceType deviceType, QString path , QWidget *parent = 0);
    ~DeviceView();
	QString path() { return mPath; }
	DeviceType deviceType() { return mDeviceType; } 

protected:
	void setName(QString name);
	void setInfo(QString info);
	void setIcon(QString iconName);

private slots:
    void settings();

private:
    Ui::DeviceView *ui;
	DeviceType mDeviceType;
	QString mPath;
};


class SinkView : public DeviceView
{
    Q_OBJECT

public:
    explicit SinkView(QString path, QWidget *parent = 0);
    virtual ~SinkView();

private:
    Sink *m_Sink;
};

class SourceView : public DeviceView
{
    Q_OBJECT

public:
    explicit SourceView(QString path, QWidget *parent = 0);
    virtual ~SourceView();

};

class PlaybackStreamView : public DeviceView
{
    Q_OBJECT

public:
    explicit PlaybackStreamView(QString path, QWidget *parent = 0);
    virtual ~PlaybackStreamView();

};

class RecordStreamView : public DeviceView
{
    Q_OBJECT

public:
    explicit RecordStreamView(QString path, QWidget *parent = 0);
    virtual ~RecordStreamView();

};

#endif // UNIT2_H
