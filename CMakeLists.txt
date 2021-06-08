cmake_minimum_required(VERSION 3.0.0)

project(BigOp CXX)

add_subdirectory(BigOpLib)

add_executable(BigOp BigOp.cpp)
set_property(TARGET BigOp PROPERTY CXX_STANDARD 20)
target_link_libraries(BigOp bigop-lib)