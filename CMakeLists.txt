cmake_minimum_required(VERSION 3.23)
project(fusilli)

include(FindPkgConfig)
find_package(SDL2pp REQUIRED)

set(CMAKE_CXX_STANDARD 20)

add_compile_options(-g)

add_executable(fusilli main.cpp)
target_link_libraries(fusilli ${SDL2pp_LIBRARIES} SDL2pp::SDL2pp)
