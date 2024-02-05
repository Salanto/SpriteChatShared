cmake_minimum_required(VERSION 3.14)

project(SpriteChatShared LANGUAGES CXX)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Core WebSockets)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Core WebSockets)

add_library(SpriteChatShared SHARED
    src/network/packets/abstractpacket.h
    src/network/packetrouter.h src/network/packetrouter.cpp
    src/network/packets/packetfactory.h src/network/packets/packetfactory.cpp
    src/network/packets/notificationpacket.h src/network/packets/notificationpacket.cpp
    src/datatypes/servertypes.h
    src/datatypes/sockettypes.h
    src/network/socket/socketinterface.h src/network/socket/socketinterface.cpp
    src/network/socket/serversocket.h src/network/socket/serversocket.cpp
    src/network/serverclient.h src/network/serverclient.cpp
)

target_include_directories(SpriteChatShared
    PRIVATE src/datatypes
    PRIVATE src/network
    PRIVATE src/network/packets
    PRIVATE src/network/socket
)

target_link_libraries(SpriteChatShared PRIVATE
    Qt${QT_VERSION_MAJOR}::Core
    Qt${QT_VERSION_MAJOR}::WebSockets
)
set_target_properties(SpriteChatShared PROPERTIES
        LIBRARY_OUTPUT_DIRECTORY $<1:${CMAKE_CURRENT_LIST_DIR}/lib>
        RUNTIME_OUTPUT_DIRECTORY $<1:${CMAKE_CURRENT_LIST_DIR}/lib>
)
