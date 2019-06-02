cmake_minimum_required(VERSION 3.12)
set(CMAKE_CXX_STANDARD 17)

project(luftwaffle)
add_subdirectory(win)

add_executable(luftwaffle
	src/main.cpp

	src/luftwaffle.hpp
)

target_link_libraries(luftwaffle PRIVATE win)
target_include_directories(luftwaffle PRIVATE win/include)
