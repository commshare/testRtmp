#
# @file CMakeLists.txt
# @author Akagi201 zhangbin
# @date 2014/10/10 2016/09/06
#

cmake_minimum_required(VERSION 2.8.4)
project(flvmuxer)

set(SOURCE_FILES src/flv.c src/rtmp.c src/xiecc_rtmp.c)

include_directories("/usr/local/include" "${PROJECT_SOURCE_DIR}/deps" "${PROJECT_SOURCE_DIR}/src")

link_directories("/usr/local/lib" "${PROJECT_SOURCE_DIR}/deps/librtmp" "${PROJECT_SOURCE_DIR}/deps/ssl")

add_executable(rtmp_push ${SOURCE_FILES})

###add for DEBUG and RELEASE
SET(CMAKE_BUILD_TYPE "Debug")  
SET(CMAKE_CXX_FLAGS_DEBUG "$ENV{CXXFLAGS} -O0 -Wall -g2 -ggdb")  
SET(CMAKE_CXX_FLAGS_RELEASE "$ENV{CXXFLAGS} -O3 -Wall")  

#this is ok
#target_link_libraries(rtmp_push "librtmp.a")

###link ssl lz cryptp and librtmp
target_link_libraries(rtmp_push "-lrtmp  -lssl -lz  -lcrypto")


