#ifndef DBUS_TYPES_H
#define DBUS_TYPES_H

#include <QMap>
#include <QList>

typedef QList<uint> DBusUIntList;
typedef QMap<QString, QByteArray> DBusPropertyList;

Q_DECLARE_METATYPE(DBusUIntList);
Q_DECLARE_METATYPE(DBusPropertyList);


#endif // DBUS_TYPES_H
