cmake_minimum_required(VERSION 3.18)

find_package(Qt5 COMPONENTS Test REQUIRED #[[Gui]])

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /utf-8")
enable_testing()


project(tst_GameInfoReadWrite LANGUAGES CXX)
add_executable(tst_GameInfoReadWrite)
target_sources(tst_GameInfoReadWrite PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/tst_GameInfoReadWrite.cc
    ${GUI_SRC_PATH}/resource.qrc)
set_target_properties(tst_GameInfoReadWrite PROPERTIES
    AUTOUIC ON
    AUTOMOC ON
    AUTORCC ON
    #CXX_STANDARD 20
    LINK_FLAGS "/SUBSYSTEM:WINDOWS /ENTRY:mainCRTStartup"
    CXX_STANDARD_REQUIRED ON
    INCLUDE_CURRENT_DIR ON)
target_include_directories(tst_GameInfoReadWrite PUBLIC
    Qt5::Test Qt::Network  ${GUI_SRC_PATH})
target_link_libraries(tst_GameInfoReadWrite PRIVATE
    Qt5::Test Qt::Network Game Infomation)

add_test(NAME tst_GameInfoReadWrite
    COMMAND tst_GameInfoReadWrite)
