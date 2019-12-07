#ifndef BYTESTREAM_H_ 
#define BYTESTREAM_H_

#include <stdint.h>
#include <string.h>
#include<stdio.h>


/*
nkwavelet 回复 akagi201:这个函数是自己写的，忘记发上来了，意思就是用相应的指针所指向的内存空间取一个字节出来，然后指针向前移动一个字节。
bytestream_get_be24()就是取3个字节拼成一个整型数，然后指针移动3个字节。现在手上没有源码，自己在机器试一下很快就出来了，不超过10行的代码。


[2015-02-11 09:36]
akagi201 回复 nkwavelet:恩, 如果方便的话, 最好补充一下吧, 我不清楚be24是大端还是小端,  我先自己实现了
*/
int bytestream_get_byte(const unsigned char ** buf);
/*输入大端，输出也大端，且可以改变指针后移*/
int bytestream_get_be24(const unsigned char ** buf);


#endif //BYTESTREAM_H_
