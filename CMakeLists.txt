cmake_minimum_required(VERSION 3.14)

project(SpriteChatShared LANGUAGES CXX)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Core)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Core)

add_library(SpriteChatShared SHARED
    src/network/abstractpacket.h
    src/network/packetrouter.h src/network/packetrouter.cpp
    src/network/packetfactory.h src/network/packetfactory.cpp
)

target_include_directories(SpriteChatShared
   PRIVATE src/network
)

target_link_libraries(SpriteChatShared PRIVATE
    Qt${QT_VERSION_MAJOR}::Core
)
set_target_properties(SpriteChatShared PROPERTIES
        LIBRARY_OUTPUT_DIRECTORY $<1:${CMAKE_CURRENT_LIST_DIR}/lib>
        RUNTIME_OUTPUT_DIRECTORY $<1:${CMAKE_CURRENT_LIST_DIR}/lib>
)
