cmake_minimum_required(VERSION 3.21)
project(netlib)

set(CXX_FLAGS "-g -Wall -std=c++11")
include_directories(${PROJECT_SOURCE_DIR}/src)

aux_source_directory(${PROJECT_SOURCE_DIR}/src SRC_LIST)
add_library(netlib SHARED ${SRC_LIST})
target_link_libraries(netlib pthread mysqlclient)
set(LIBRARY_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/lib)
