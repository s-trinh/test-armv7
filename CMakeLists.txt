project(test-armv7)

cmake_minimum_required(VERSION 3.0)

find_package(VISP)

include_directories(${VISP_INCLUDE_DIRS})
add_executable(test-scandir test-scandir.cpp)
set_property(TARGET test-scandir PROPERTY CXX_STANDARD 17)

add_executable(test-create-seq test-create-seq.cpp)
target_link_libraries(test-create-seq ${VISP_LIBRARIES})

add_executable(test-read-seq test-read-seq.cpp)
target_link_libraries(test-read-seq ${VISP_LIBRARIES})
