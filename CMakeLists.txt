cmake_minimum_required(VERSION 3.16)

project(HojaCalculoAED LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

file(GLOB_RECURSE PROJECT_SOURCES CONFIGURE_DEPENDS
    "${CMAKE_SOURCE_DIR}/src/*.cpp"
)

add_executable(HojaCalculoAED ${PROJECT_SOURCES})

target_include_directories(HojaCalculoAED PRIVATE
    "${CMAKE_SOURCE_DIR}/include"
)

find_package(SFML 2.5 COMPONENTS system window graphics REQUIRED)

target_link_libraries(HojaCalculoAED PRIVATE
    sfml-system
    sfml-window
    sfml-graphics
)