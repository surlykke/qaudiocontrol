#ifndef MIXER_H
#define MIXER_H

#include <QMainWindow>
#include <QDBusObjectPath>

#include "paproxy.h"

namespace Ui {
class Mixer;
}

class QGraphicsScene;
class DeviceView;

class Mixer : public QMainWindow
{
    Q_OBJECT

public:
    explicit Mixer(QWidget *parent = 0);
    ~Mixer();

public slots:
	void newSink(QDBusObjectPath objectPath);
	void newSource(QDBusObjectPath objectPath);
	void newPlaybackStream(QDBusObjectPath objectPath);
	void newRecordStream(QDBusObjectPath objectPath);

	void deviceRemoved(QDBusObjectPath objectPath);

private:
	void addDevice(DeviceView *deviceView);

    void doLayout();

    Ui::Mixer *ui;
    QGraphicsScene* mScene;
	PAProxy *paProxy;

	QMap<QString, DeviceView*> deviceViews;
};

#endif // MIXER_H
