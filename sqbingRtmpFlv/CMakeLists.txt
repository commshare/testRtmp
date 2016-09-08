#
# @file CMakeLists.txt
# @author  zhangbin
# @date  2016/09/08
#

cmake_minimum_required(VERSION 2.8.4)
project(infinite_push_flv)

set(SOURCE_FILES src/main.cc)

include_directories("/usr/local/include" "${PROJECT_SOURCE_DIR}/deps" "${PROJECT_SOURCE_DIR}/src")

link_directories("/usr/local/lib" "${PROJECT_SOURCE_DIR}/deps/librtmp" "${PROJECT_SOURCE_DIR}/deps/ssl")

add_executable(infinite_push_flv ${SOURCE_FILES})

###add for DEBUG and RELEASE
SET(CMAKE_BUILD_TYPE "Debug")  
SET(CMAKE_CXX_FLAGS_DEBUG "$ENV{CXXFLAGS} -O0 -Wall -g2 -ggdb")  
SET(CMAKE_CXX_FLAGS_RELEASE "$ENV{CXXFLAGS} -O3 -Wall")  

#this is ok
#target_link_libraries(rtmp_push "librtmp.a")

###link ssl lz cryptp and librtmp
target_link_libraries(infinite_push_flv "-lrtmp  -lssl -lz  -lcrypto")


