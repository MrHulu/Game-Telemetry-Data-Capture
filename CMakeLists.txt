cmake_minimum_required(VERSION 3.14)

project(Game-Telemetry-Data-Capture LANGUAGES CXX)

include_directories(Src)
set(ROOT_SRC_PATH ${CMAKE_CURRENT_SOURCE_DIR})
set(ROOT_BIN_PATH ${CMAKE_CURRENT_BINARY_DIR})
set(3RD_SRC_PATH ${CMAKE_CURRENT_LIST_DIR}/3rdparty)
set(3RD_INSTALL_PATH ${CMAKE_CURRENT_BINARY_DIR}/3rdparty)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_subdirectory(Src)
#add_subdirectory(Tests)
#add_subdirectory(3rdparty)
