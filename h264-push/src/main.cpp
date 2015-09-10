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
  
  int main(int argc,char* argv[])  
  {  
      CRTMPStream rtmpSender;  
    
      bool bRet = rtmpSender.Connect("rtmp://192.168.1.104/live/test");  
    
      rtmpSender.SendH264File("E:\\video\\test.264");  
    
      rtmpSender.Close();  
  }  
