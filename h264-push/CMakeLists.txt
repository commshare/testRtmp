#
# @file CMakeLists.txt
# @author Akagi201
# @date 2014/10/10
#

cmake_minimum_required(VERSION 2.8.4)
project(rtmp_h264_push)

set(SOURCE_FILES src/main.cpp src/RTMPStream.cpp)

add_subdirectory(../librtmp/ "${PROJECT_SOURCE_DIR}/deps/librtmp")

include_directories("/usr/local/include" "${PROJECT_SOURCE_DIR}/deps/librtmp")

link_directories("/usr/local/ssl/lib" "${PROJECT_SOURCE_DIR}/deps/librtmp")

add_executable(rtmp_h264_push ${SOURCE_FILES})

target_link_libraries(rtmp_h264_push  "-lrtmp  -lssl -lz  -lcrypto")

