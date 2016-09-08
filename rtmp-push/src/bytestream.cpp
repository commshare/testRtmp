#include"bytestream.h"


/*测试能否改变外部的pHeader2*/
#define TEST_CHANGE_pHeader2 0
/*buf是大端，返回的也是大端*/
int bytestream_get_byte(const unsigned char ** buf){
	const	 unsigned char *p=*buf;
  // printf("*buf [%c]\n   [%d] \n [%d]\n",*p,*p,(*p)&&0x000000FF);

	int a= (int)(*p);
	(*buf)=(*buf) + 1;
 	return a;
}

/*输入大端，输出也大端，且可以改变指针后移*/
int bytestream_get_be24(const unsigned char ** buf){
	 const unsigned char *p=*buf;
     unsigned char a=(*p);
     unsigned char b=(*(p+1));
     unsigned char c=(*(p+2));
    int d=(a<<16) | (b<<8) | (c) ;
    /*d和e的计算方式是一样的*/
    int e= (a<<16) +(b<<8) + (c) ;
    printf("###e[%d]\n",e);
//	printf("a[%d] \n b[%d] \nc[%d] \n d[%d]\n",a,b,c,d);
//	 printf("#2#move to next \n");
	 #if TEST_CHANGE_pHeader2
	 p=p+3;/*不管用，改变的是p,不会改变外部的pHeader2*/
	 printf("(*p)[%d]\n",*p);
	 #else
//	buf=buf+1;  /*不管用，改变的是buf*/
 p=p+3;
(*buf)=(*buf)+3;

	 printf("(*p)[%d] **buf [%d] d[%d]\n",*p,**buf,d);
	 #endif
     return d;
}
