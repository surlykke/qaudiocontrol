cmake_minimum_required(VERSION 2.8)
project(qaudiocontrol)
include(FindPkgConfig)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set ( qaudiocontrol_HDRS
        dbus_types.h
        device_proxy.h
        deviceview.h
        mixer.h
        paproxy.h
)

set ( qaudiocontrol_SRCS
        device_proxy.cpp
        deviceview.cpp
        main.cpp
        mixer.cpp
        paproxy.cpp
)

set ( qaudiocontrol_UIS
        deviceview.ui
        mixer.ui
        test.ui
)

set ( qaudiocontrol_MOCS
        dbus_types.h
        device_proxy.h
        deviceview.h
        mixer.h
        paproxy.h
)

set ( qaudiocontrol_RSCS

)

set(CMAKE_AUTOMOC ON)

find_package (Qt5Core)
find_package (Qt5Gui)
find_package (Qt5Widgets)
find_package (Qt5DBus)
QT5_WRAP_UI(UIS ${qaudiocontrol_UIS})
QT5_ADD_RESOURCES(RSCS ${qaudiocontrol_RSCS})
QT5_WRAP_CPP(MOCS ${qaudiocontrol_MOCS})

add_executable ( qaudiocontrol
                 ${qaudiocontrol_SRCS}
                 ${qaudiocontrol_HDRS}
                 ${UIS}
                 ${qaudiocontrol_MOCS}
                 ${qaudiocontrol_RSCS}
)


qt5_use_modules(qaudiocontrol Core)
qt5_use_modules(qaudiocontrol Gui)
qt5_use_modules(qaudiocontrol Widgets)
qt5_use_modules(qaudiocontrol DBus)

