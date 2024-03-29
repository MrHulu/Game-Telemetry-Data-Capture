cmake_minimum_required(VERSION 3.14)

project(Game-Telemetry-Data-Capture)

include_directories(Src)
set(ROOT_SRC_PATH ${CMAKE_CURRENT_SOURCE_DIR})
set(ROOT_BIN_PATH ${CMAKE_CURRENT_BINARY_DIR})
set(GUI_SRC_PATH ${CMAKE_CURRENT_LIST_DIR}/src)
set(3RD_SRC_PATH ${CMAKE_CURRENT_LIST_DIR}/3rdparty)
set(3RD_INSTALL_PATH ${CMAKE_CURRENT_BINARY_DIR}/3rdparty)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /utf-8 /std:c++latest")

find_package(Qt5 COMPONENTS Gui Core Network REQUIRED)

# ----------  Utils  ----------
add_library(Utils STATIC)
target_sources(Utils PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/Src/Utils/JsonFileAnalysis.h
    ${CMAKE_CURRENT_SOURCE_DIR}/Src/Utils/JsonFileAnalysis.cc
    ${CMAKE_CURRENT_SOURCE_DIR}/Src/Utils/VersionCompare.cc)
set_target_properties(Utils PROPERTIES
    AUTOUIC ON
    AUTOMOC ON
    AUTORCC ON
    CXX_STANDARD 20
    CXX_STANDARD_REQUIRED ON
    INCLUDE_CURRENT_DIR ON)
target_include_directories(Utils PUBLIC
    Qt5::Core )
target_link_libraries(Utils PRIVATE
    Qt5::Core Qt5::Network)



# ----------  Infomation  ----------
add_library(Infomation STATIC)
target_sources(Infomation PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/Src/Environment/documentsPath.cc)
set_target_properties(Infomation PROPERTIES
    AUTOUIC ON
    AUTOMOC ON
    AUTORCC ON
    #CXX_STANDARD 20
    CXX_STANDARD_REQUIRED ON
    INCLUDE_CURRENT_DIR ON)
target_include_directories(Infomation PUBLIC
    Qt5::Core )
target_link_libraries(Infomation PRIVATE
    Qt5::Core)


# ----------  Data  ----------
add_library(Data STATIC)
target_sources(Data PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/Src/Data/TelemetryDataBuffer.h
    ${CMAKE_CURRENT_SOURCE_DIR}/Src/Data/TelemetryDataBuffer.cc
    ${CMAKE_CURRENT_SOURCE_DIR}/Src/Data/TelemetryDataTableModel.h
    ${CMAKE_CURRENT_SOURCE_DIR}/Src/Data/TelemetryDataTableModel.cc
)
set_target_properties(Data PROPERTIES
    AUTOUIC ON
    AUTOMOC ON
    AUTORCC ON
    #CXX_STANDARD 20
    CXX_STANDARD_REQUIRED ON
    INCLUDE_CURRENT_DIR ON)
target_include_directories(Data PUBLIC
    Qt5::Core )
target_link_libraries(Data PRIVATE
    Qt5::Core)

# -------   Game   -----------
add_library(Game STATIC)
target_sources(Game PRIVATE
    "Src/Game/Game.h"
    "Src/Game/Game.cc"
    "Src/Game/GameWithUdp.h"
    "Src/Game/GameWithUdp.cc"
    "Src/Game/Capturer.h"
    "Src/Game/Capturer.cc"
    "Src/Game/CapturerWithUdp.h"
    "Src/Game/CapturerWithUdp.cc"

    ${CMAKE_CURRENT_SOURCE_DIR}/Src/Game/GameManager.h
    ${CMAKE_CURRENT_SOURCE_DIR}/Src/Game/GameManager.cc
    ${CMAKE_CURRENT_SOURCE_DIR}/Src/Game/GameRunMonitoringHelper.h
    ${CMAKE_CURRENT_SOURCE_DIR}/Src/Game/GameRunMonitoringHelper.cc
    ${CMAKE_CURRENT_SOURCE_DIR}/Src/Game/GameInfoHelper.h
    ${CMAKE_CURRENT_SOURCE_DIR}/Src/Game/GameInfoHelper.cc
    ${CMAKE_CURRENT_SOURCE_DIR}/Src/Game/GameInfoHelperFileAnalysis.h
    ${CMAKE_CURRENT_SOURCE_DIR}/Src/Game/GameInfoHelperFileAnalysis.cc
    )
set_target_properties(Game PROPERTIES
    AUTOUIC ON
    AUTOMOC ON
    AUTORCC ON
    CXX_STANDARD 20
    CXX_STANDARD_REQUIRED ON
    INCLUDE_CURRENT_DIR ON)
target_include_directories(Game PUBLIC
    Qt5::Core Qt5::Network ${GUI_SRC_PATH})
target_link_libraries(Game PRIVATE
    Qt5::Core Qt5::Network
    Infomation Utils Data
    ACGame ACCGame
    Dirt2Game Dirt4Game)


# ------ Assetto Corsa --------
add_library(ACGame STATIC)
target_sources(ACGame PRIVATE
    "Src/Game/Assetto Corsa/ACGame.h"
    "Src/Game/Assetto Corsa/ACGame.cc"
    "Src/Game/Assetto Corsa/ACTelemetryDataCapturer.h"
    "Src/Game/Assetto Corsa/ACTelemetryDataCapturer.cc"
    "Src/Game/Assetto Corsa/SharedMemoryPacket.h"
    )
set_target_properties(ACGame PROPERTIES
    AUTOUIC ON
    AUTOMOC ON
    AUTORCC ON
    CXX_STANDARD 20
    CXX_STANDARD_REQUIRED ON
    INCLUDE_CURRENT_DIR ON)
target_include_directories(ACGame PUBLIC
    Qt5::Core ${GUI_SRC_PATH})
target_link_libraries(ACGame PRIVATE
    Qt5::Core)


# ------ Assetto Corsa Competizione --------
add_library(ACCGame STATIC)
target_sources(ACCGame PRIVATE
    "Src/Game/Assetto Corsa Competizione/ACCGame.h"
    "Src/Game/Assetto Corsa Competizione/ACCGame.cc"
    "Src/Game/Assetto Corsa Competizione/ACCTelemetryDataCapturer.h"
    "Src/Game/Assetto Corsa Competizione/ACCTelemetryDataCapturer.cc"
    "Src/Game/Assetto Corsa Competizione/SharedMemoryPacket.h"
    )
set_target_properties(ACCGame PROPERTIES
    AUTOUIC ON
    AUTOMOC ON
    AUTORCC ON
    CXX_STANDARD 20
    CXX_STANDARD_REQUIRED ON
    INCLUDE_CURRENT_DIR ON)
target_include_directories(ACCGame PUBLIC
    Qt5::Core ${GUI_SRC_PATH})
target_link_libraries(ACCGame PRIVATE
    Qt5::Core)


# ------ DiRT Rally 2.0 --------
add_library(Dirt2Game STATIC)
target_sources(Dirt2Game PRIVATE
    "Src/Game/DiRT Rally 2.0/DirtRally2Game.h"
    "Src/Game/DiRT Rally 2.0/DirtRally2Game.cc"
    "Src/Game/DiRT Rally 2.0/DirtRally2TelemetryDataCapturer.h"
    "Src/Game/DiRT Rally 2.0/DirtRally2TelemetryDataCapturer.cc"
    "Src/Game/DiRT Rally 2.0/UdpPacket.h"
    )
set_target_properties(Dirt2Game PROPERTIES
    AUTOUIC ON
    AUTOMOC ON
    AUTORCC ON
    CXX_STANDARD 20
    CXX_STANDARD_REQUIRED ON
    INCLUDE_CURRENT_DIR ON)
target_include_directories(Dirt2Game PUBLIC
    Qt5::Core ${GUI_SRC_PATH})
target_link_libraries(Dirt2Game PRIVATE
    Qt5::Core Qt5::Network)


# ------ DiRT 4 --------
add_library(Dirt4Game STATIC)
target_sources(Dirt4Game PRIVATE
    "Src/Game/DiRT 4/Dirt4Game.h"
    "Src/Game/DiRT 4/Dirt4Game.cc"
    "Src/Game/DiRT 4/Dirt4TelemetryDataCapturer.h"
    "Src/Game/DiRT 4/Dirt4TelemetryDataCapturer.cc"
    "Src/Game/DiRT 4/UdpPacket.h"
    )
set_target_properties(Dirt4Game PROPERTIES
    AUTOUIC ON
    AUTOMOC ON
    AUTORCC ON
    CXX_STANDARD 20
    CXX_STANDARD_REQUIRED ON
    INCLUDE_CURRENT_DIR ON)
target_include_directories(Dirt4Game PUBLIC
    Qt5::Core ${GUI_SRC_PATH})
target_link_libraries(Dirt4Game PRIVATE
    Qt5::Core Qt5::Network)


add_subdirectory(Src)
add_subdirectory(Tests)
#add_subdirectory(3rdparty)
