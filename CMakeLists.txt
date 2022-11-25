cmake_minimum_required (VERSION 3.0)
project (upixel)

find_package(OpenCV REQUIRED)

include_directories(${OpenCV_INCLUDE_DIRS})
link_directories(${OpenCV_LIBS})

add_executable(app src/main.cpp)
target_link_libraries(app ${OpenCV_LIBS})
