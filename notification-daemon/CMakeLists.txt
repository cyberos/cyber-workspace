project(cyber-notification-daemon)
set(TARGET cyber-notification-daemon)

set(SOURCES
    application.cpp
    main.cpp
)

qt5_add_dbus_adaptor(DBUS_SOURCES
                     org.freedesktop.Notifications.xml
                     application.h Application
                     sessionadaptor SessionAdaptor)
set_source_files_properties(${DBUS_SOURCES} PROPERTIES SKIP_AUTOGEN ON)

add_executable(${TARGET} ${SOURCES} ${DBUS_SOURCES})
target_link_libraries(${TARGET}
        Qt5::Core
        Qt5::Gui
        Qt5::Widgets
        Qt5::DBus
)

install(TARGETS ${TARGET} DESTINATION /usr/bin)
