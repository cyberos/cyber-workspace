find_package(PkgConfig)
pkg_check_modules(POLKIT_AGENT REQUIRED polkit-agent-1)
message(STATUS "polkit agent: ${POLKIT_AGENT_INCLUDE_DIRS} ${POLKIT_AGENT_LIBRARIES}")

find_package(PolkitQt5-1 REQUIRED)

include_directories(
    ${POLKIT_AGENT_INCLUDE_DIRS}
    "${POLKITQT-1_INCLUDE_DIR}"
)

add_executable(cyber-polkit-agent
    main.cpp
    polkitagentlistener.cpp
    dialog.cpp
    qml.qrc
)

target_link_libraries(cyber-polkit-agent
        Qt5::Core
        Qt5::Widgets
        Qt5::Quick
        Qt5::QuickControls2

        MeuiKit

        ${POLKITQT-1_CORE_LIBRARY}
        ${POLKITQT-1_AGENT_LIBRARY}
        ${POLKIT_AGENT_LDFLAGS}
)

install(TARGETS cyber-polkit-agent
    DESTINATION /usr/bin
    COMPONENT Runtime
)

install(FILES
    cyber-polkit-agent.desktop
    DESTINATION "/etc/xdg/autostart"
    COMPONENT Runtime
)
