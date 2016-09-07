/*
 * @file main.cpp
 * @author Akagi201
 * @date 2015/02/10
 */
#include"lwlog/lwlog.h"
#include "CRtmpStream.h"

int main(int argc, char *argv[]) {
    bool ret = FALSE;
    const char *url = "rtmp://172.19.42.177:1935/live/test";
    RTMP_LogSetLevel(RTMP_LOGALL);
    CRtmpStream rtmpStream;
    ret = rtmpStream.Connect(url);

    if(ret == FALSE){
        lwlog_err("connect fail");
        return -1;
    }

    const char *filename = "input.flv";
    ret = rtmpStream.SendFlvFile(filename);

    return 0;
}