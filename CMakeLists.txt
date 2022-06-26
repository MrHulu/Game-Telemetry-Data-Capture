cmake_minimum_required(VERSION 3.14)

project(Game-Telemetry-Data-Capture LANGUAGES CXX)

include_directories(Src)
set(ROOT_SRC_PATH ${CMAKE_CURRENT_SOURCE_DIR})
set(ROOT_BIN_PATH ${CMAKE_CURRENT_BINARY_DIR})
set(3RD_SRC_PATH ${CMAKE_CURRENT_LIST_DIR}/3rdparty)
set(3RD_INSTALL_PATH ${CMAKE_CURRENT_BINARY_DIR}/3rdparty)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt5 COMPONENTS Gui Core Network REQUIRED)


# -------   Game   -----------
add_library(Game STATIC)
target_sources(Game PRIVATE
    "Src/Game/GameWithUdp.h"
    "Src/Game/GameWithUdp.cc"
    "Src/Game/Game.h"
    "Src/Game/Game.cc"
    )
set_target_properties(Game PROPERTIES
    AUTOUIC ON
    AUTOMOC ON
    AUTORCC ON
    CXX_STANDARD 20
    CXX_STANDARD_REQUIRED ON
    INCLUDE_CURRENT_DIR ON)
target_link_libraries(Game PRIVATE
    Qt5::Core Qt5::Network)


add_subdirectory(Src)
#add_subdirectory(Tests)
#add_subdirectory(3rdparty)
