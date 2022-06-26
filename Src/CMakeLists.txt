cmake_minimum_required(VERSION 3.14)

find_package(Qt5 COMPONENTS Core Widgets Quick QuickControls2 REQUIRED)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /utf-8")
set(SOFTWARE_NAME "Telemetry Data Capture Tool")

enable_testing()

add_executable(Game-Telemetry-Data-Capture)
target_sources(Game-Telemetry-Data-Capture PRIVATE
    #${CMAKE_CURRENT_BINARY_DIR}/Game-Telemetry-Data-Capture.rc
    ${CMAKE_CURRENT_SOURCE_DIR}/main.cc
    ${CMAKE_CURRENT_SOURCE_DIR}/Gui/resource.qrc
    )
set_target_properties(Game-Telemetry-Data-Capture PROPERTIES
    AUTOUIC ON
    AUTOMOC ON
    AUTORCC ON
    #CXX_STANDARD 20
    CXX_STANDARD_REQUIRED ON
    INCLUDE_CURRENT_DIR ON
    LINK_FLAGS "/SUBSYSTEM:WINDOWS /ENTRY:mainCRTStartup"
    OUTPUT_NAME "${SOFTWARE_NAME}")
target_include_directories(Game-Telemetry-Data-Capture PUBLIC
    Qt5::Core Qt5::Quick Qt5::QuickControls2 #${GUI_SRC_PATH}
	)
target_link_libraries(Game-Telemetry-Data-Capture PRIVATE
    Qt5::Core Qt5::Quick Qt5::QuickControls2 Game
    )
#add_custom_command(TARGET Game-Telemetry-Data-Capture
#    DEPENDS ${QM_FILES}
#    COMMAND (if not exist translations ( mkdir "translations" ))
#    COMMAND (for %i in (${QM_BATCH_FILES_PATH}) do (xcopy %i "translations" /D /Y))
#    WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR})
#add_custom_command(TARGET d00-pc_gui
#    DEPENDS ${ROOT_BIN_PATH}/resource.rcc
#    COMMAND (xcopy resource.rcc "src" /D /Y)
#    WORKING_DIRECTORY ${ROOT_BIN_PATH})
