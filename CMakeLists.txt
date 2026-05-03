cmake_minimum_required(VERSION 3.16)

project(HojaCalculoAED LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

file(GLOB_RECURSE PROJECT_SOURCES CONFIGURE_DEPENDS
    "${CMAKE_SOURCE_DIR}/src/*.cpp"
)

add_executable(HojaCalculoAED ${PROJECT_SOURCES})

target_include_directories(HojaCalculoAED PRIVATE
    "${CMAKE_SOURCE_DIR}/include"
)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets)
find_package(Qt${QT_VERSION_MAJOR} COMPONENTS Widgets REQUIRED)

target_link_libraries(HojaCalculoAED PRIVATE
    Qt${QT_VERSION_MAJOR}::Widgets
)