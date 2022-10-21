project(test-armv7)

cmake_minimum_required(VERSION 3.0)

add_executable(test-scandir test-scandir.cpp)
set_property(TARGET test-scandir PROPERTY CXX_STANDARD 17)
