#include <QApplication>
#include <QIcon>
#include <QDebug>
#include "mixer.h"
#include "paproxy.h"
#include "dbus_types.h"
#include <QDBusMetaType>

int main(int argc, char *argv[])
{
    qDBusRegisterMetaType<DBusUIntList>();
    qDBusRegisterMetaType<DBusPropertyList>();

    QApplication a(argc, argv);

    QIcon::setThemeName("elementary");

    Mixer m;
    m.show();


    return a.exec();
}


