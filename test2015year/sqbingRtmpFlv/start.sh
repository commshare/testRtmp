#!/bin/sh
echo "copy this file to build/start.sh" 
echo "start...push flv ...."
./infinite_push_flv -i ../../rtmp-push/build/input.flv -o rtmp://172.19.42.177:1935/live/test
