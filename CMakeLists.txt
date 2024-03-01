cmake_minimum_required(VERSION 3.14)
include(FetchContent)

project(SpriteChatShared LANGUAGES CXX)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 REQUIRED COMPONENTS Core WebSockets Network)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Core WebSockets Network)

if (Qt6_VERSION VERSION_LESS 6.5)
    message(FATAL_ERROR "This project only works with Qt 6.5 or higher!")
endif()

include(FetchContent)
message("Fetching bit7z")
FetchContent_Declare(
    bit7z
    GIT_REPOSITORY https://github.com/rikyoz/bit7z.git
    GIT_TAG v4.0.5
    SOURCE_DIR ${CMAKE_CURRENT_LIST_DIR}/third-party/bit7z
)
set(BIT7Z_AUTO_FORMAT ON)
FetchContent_MakeAvailable(bit7z)


add_library(SpriteChatShared SHARED
    src/spritechatshared_global.h
    src/network/packets/abstractpacket.h
    src/network/packets/packetrouter.h src/network/packets/packetrouter.cpp
    src/network/packets/packetfactory.h src/network/packets/packetfactory.cpp
    src/network/packets/notificationpacket.h src/network/packets/notificationpacket.cpp
    src/datatypes/servertypes.h
    src/datatypes/sockettypes.h
    src/network/serversocket.h src/network/serversocket.cpp
    src/network/serverclient.h src/network/serverclient.cpp
    src/network/packets/serverhellopacket.h src/network/packets/serverhellopacket.cpp
    src/network/packets/hellopacket.h src/network/packets/hellopacket.cpp
    src/network/packets/charlistpacket.h src/network/packets/charlistpacket.cpp
    src/network/packets/charlisttakenpacket.h src/network/packets/charlisttakenpacket.cpp
    src/network/packets/characterpacket.h src/network/packets/characterpacket.cpp
    src/datatypes/musictypes.h
    src/network/packets/selectmusicpacket.h src/network/packets/selectmusicpacket.cpp
    src/network/packets/musicpacket.h src/network/packets/musicpacket.cpp
    src/network/packets/musiclistpacket.h src/network/packets/musiclistpacket.cpp
    src/network/packets/locationlistpacket.h src/network/packets/locationlistpacket.cpp
    src/datatypes/areatypes.h
    src/network/packets/locationpacket.h src/network/packets/locationpacket.cpp
    src/network/packets/backgroundpacket.h src/network/packets/backgroundpacket.cpp
    src/network/packets/sidelistpacket.h src/network/packets/sidelistpacket.cpp
    src/network/packets/setsidepacket.h src/network/packets/setsidepacket.cpp
    src/network/packets/chatpacket.h src/network/packets/chatpacket.cpp
    src/datatypes/animationtypes.h
    src/network/packets/viewportpacket.h src/network/packets/viewportpacket.cpp
    src/viewport/abstractanimationevent.h
    src/datatypes/areatypes.cpp
    src/datatypes/coordinatortypes.h
    src/network/coordinatorclient.h src/network/coordinatorclient.cpp
    src/network/coordinatoradvertiser.h src/network/coordinatoradvertiser.cpp
    src/datatypes/loadingtypes.h
    src/assets/mount.h src/assets/mount.cpp
    src/assets/mountaccess.h src/assets/mountaccess.cpp
    src/datatypes/assettypes.h
)

target_include_directories(SpriteChatShared
    PUBLIC src
    PUBLIC src/datatypes
    PUBLIC src/network
    PUBLIC src/network/packets
    PUBLIC src/network/socket
    PUBLIC src/viewport
    PRIVATE third-party/bit7z/include
)

target_link_libraries(SpriteChatShared PRIVATE
    Qt${QT_VERSION_MAJOR}::Core
    Qt${QT_VERSION_MAJOR}::WebSockets
    Qt${QT_VERSION_MAJOR}::Network
    bit7z
)

target_compile_definitions(SpriteChatShared PRIVATE
    SPRITECHATSHARED_LIBRARY TRUE
)

set_target_properties(SpriteChatShared PROPERTIES
    LIBRARY_OUTPUT_DIRECTORY $<1:${CMAKE_SOURCE_DIR}/bin>
    RUNTIME_OUTPUT_DIRECTORY $<1:${CMAKE_SOURCE_DIR}/bin>
)
