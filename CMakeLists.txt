cmake_minimum_required(VERSION 3.17)
project(darknet C)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -Wno-unused-result -Wno-unknown-pragmas -Wfatal-errors -fPIC")

set(OPTS -Ofast)
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${OPTS}")
set(NVCC nvcc)

find_package(OpenCV REQUIRED)

include_directories(src include)

file(GLOB HEADERS src/*.h include/*.h)
file(GLOB SOURCES src/*.c examples/*.c)

add_executable(darknet ${SOURCES})

target_link_libraries(darknet ${OpenCV_LIBS} -lpthread -lm)

