#
# @file CMakeLists.txt
# @author Akagi201
# @date 2014/10/10
#

cmake_minimum_required(VERSION 2.8.4)
project(rtmp_h264_push)

set(SOURCE_FILES src/main.cpp src/RTMPStream.cpp)

add_subdirectory(../librtmp/ ../librtmp/build/)

include_directories("/usr/local/include" "../librtmp" "deps/lwlog/")

link_directories("/usr/local/ssl/lib" ../librtmp/build/)

add_executable(rtmp_h264_push ${SOURCE_FILES})

target_link_libraries(rtmp_h264_push  "-lrtmp  -lssl -lz  -lcrypto")

