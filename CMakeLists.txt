#cmake_minimum_required(VERSION 3.5)
project(batch)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES exper2.cpp ssp_pair.cpp ecn.cpp zzn2.cpp zzn.cpp big.cpp)
#set(SOURCE_FILES big.cpp collision2.cpp)
add_executable(exper ${SOURCE_FILES})
target_link_libraries(exper ${PROJECT_SOURCE_DIR}/miracl.a)
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/build)