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

qt5_wrap_ui(UIS ${qaudiocontrol_UIS})
qt5_add_resources(RSCS ${qaudiocontrol_RSCS})
qt5_wrap_cpp(mocs ${qaudiocontrol_mocs})

set_source_files_properties(org.PulseAudio.Core1.Device.xml PROPERTIES INCLUDE dbus_types.h)
qt5_add_dbus_interface(DBUS_STUFF org.PulseAudio.Core1.Device.xml device_proxy)

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

