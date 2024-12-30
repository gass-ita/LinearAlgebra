cmake_minimum_required(VERSION 3.5.0)
project(LinearAlgebra VERSION 0.1.0 LANGUAGES C CXX)

# sdl2
find_package(SDL2 CONFIG REQUIRED)

# Enable C++17 or newer standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

add_executable(LinearAlgebra main.cpp)

target_link_libraries(LinearAlgebra
    PRIVATE
    $<TARGET_NAME_IF_EXISTS:SDL2::SDL2main>
    $<IF:$<TARGET_EXISTS:SDL2::SDL2>,SDL2::SDL2,SDL2::SDL2-static>
)


