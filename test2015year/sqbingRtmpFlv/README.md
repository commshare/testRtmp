infinite_push_rtmp
Build Status

https://github.com/sqbing/infinite_push_rtmp

基于librtmp实现的流推送程序，循环读取输入的flv文件，并推送至远端的RTMP服务器。

RTMP push program based on librtmp. Reads in one flv file, and pushes to remote RTMP server infinitely by adapting timestamp.

编译/Compile
g++ -i main.cc -l rtmp -o infinite_push

运行/Run
./infinite_push -i ~/whatever.flv -o rtmp://xxx.xxx.xxx.xxx/live/test

测试/Test
已测试，运行良好:

crtmpserver-1.1_beta
nginx-rtmp-module-1.1.4