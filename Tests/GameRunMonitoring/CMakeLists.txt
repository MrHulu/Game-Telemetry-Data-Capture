cmake_minimum_required(VERSION 3.18)

find_package(Qt5 COMPONENTS Test REQUIRED #[[Gui]])

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /utf-8")
enable_testing()


project(tst_GameRunMonitoring LANGUAGES CXX)
add_executable(tst_GameRunMonitoring)
target_sources(tst_GameRunMonitoring PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/tst_GameRunMonitoring.cc)
set_target_properties(tst_GameRunMonitoring PROPERTIES
    AUTOUIC ON
    AUTOMOC ON
    AUTORCC ON
    #CXX_STANDARD 20
    LINK_FLAGS "/SUBSYSTEM:WINDOWS /ENTRY:mainCRTStartup"
    CXX_STANDARD_REQUIRED ON
    INCLUDE_CURRENT_DIR ON)
target_include_directories(tst_GameRunMonitoring PUBLIC
    Qt5::Test ${GUI_SRC_PATH})
target_link_libraries(tst_GameRunMonitoring PRIVATE
    Qt5::Test Game )

add_test(NAME tst_GameRunMonitoring
    COMMAND tst_GameRunMonitoring)
