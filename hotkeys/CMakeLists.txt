cmake_minimum_required(VERSION 3.20)

project(cyber-hotkeys)

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(QT Core Widgets)
find_package(Qt5 REQUIRED ${QT})
find_library(QHotkey QHotkey REQUIRED)

set(SRCS
	main.cpp
	hotkeys.cpp
)

add_executable(cyber-hotkeys ${SRCS})
target_link_libraries(cyber-hotkeys
	Qt5::Core
	Qt5::Widgets
	${QHotkey}
)
install(TARGETS cyber-hotkeys DESTINATION /usr/bin)
