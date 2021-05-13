project(cyber-notification-daemon)
set(TARGET cyber-notification-daemon)

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(SOURCES
    application.cpp
    main.cpp
    notification.cpp
    notificationmanager.cpp
    iconthemeprovider.cpp
    qml_notificationbase.cpp
    desktopproperties.cpp

    qml/resources.qrc
)

set(QT Core Gui Quick QuickControls2 Widgets DBus)
find_package(Qt5 REQUIRED ${QT})
find_package(KF5WindowSystem REQUIRED)

qt5_add_dbus_adaptor(DBUS_SOURCES
                     org.freedesktop.Notifications.xml
                     notificationmanager.h NotificationManager
                     notificationadaptor NotificationAdaptor)
set_source_files_properties(${DBUS_SOURCES} PROPERTIES SKIP_AUTOGEN ON)

add_executable(${TARGET} ${SOURCES} ${DBUS_SOURCES})
target_link_libraries(${TARGET}
        Qt5::Core
        Qt5::Gui
        Qt5::Quick
        Qt5::QuickControls2
        Qt5::Widgets
        Qt5::DBus

        KF5::WindowSystem
)

install(TARGETS ${TARGET} DESTINATION /usr/bin)
