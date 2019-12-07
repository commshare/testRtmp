/*************************************************************************
	> File Name: main.cpp
	> Author:
	> Mail:
	> Created Time: 2015年09月10日 星期四 10时05分06秒
 ************************************************************************/

#include<iostream>
using namespace std;
#include <stdio.h>
#include "RTMPStream.h"

#include"lwlog.h"

#define H264_RAW "/home/zhangbin/xlive/rtmppush/testak201/720p.h264.raw"
#define srv_url "rtmp://192.168.10.33/live/liveStream"

  int main(int argc,char* argv[])
  {
      CRTMPStream rtmpSender;
      char *file=H264_RAW;
      if(argc == 1)
      {
          lwlog_debug("no input file ");
      }else
        file=argv[1];
      lwlog_info("use the 264 file [%s]",file)

      bool bRet = rtmpSender.Connect(srv_url);

      rtmpSender.SendH264File(file);

      rtmpSender.Close();
  }
