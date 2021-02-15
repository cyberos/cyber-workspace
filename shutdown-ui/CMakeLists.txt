project(cyber-shutdown)

add_executable(cyber-shutdown
    main.cpp
    actions.cpp
    qml.qrc
)

target_link_libraries(cyber-shutdown
        Qt5::Core
        Qt5::Widgets
        Qt5::Quick
        Qt5::QuickControls2
        Qt5::DBus
)

file(GLOB TS_FILES translations/*.ts)
qt5_create_translation(QM_FILES ${TS_FILES})
add_custom_target(shutdown-translations DEPENDS ${QM_FILES} SOURCES ${TS_FILES})
add_dependencies(cyber-shutdown shutdown-translations)
install(FILES ${QM_FILES} DESTINATION /usr/share/cyber-shutdown/translations)

install(TARGETS cyber-shutdown RUNTIME DESTINATION /usr/bin)