cmake_minimum_required(VERSION 3.0)

project(data_generator)

add_executable(data_generator main.cpp)
set_target_properties(data_generator PROPERTIES CXX_STANDARD 20)
