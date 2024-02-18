cmake_minimum_required(VERSION 3.12)
project(Challenge)

find_package(OpenCV REQUIRED)

add_executable(main.exe main.cpp)
target_link_libraries(main.exe ${OpenCV_LIBS})
