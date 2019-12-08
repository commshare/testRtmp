#pragma once


#define RTMP_LIB_VERSION	0x020400	/* 2.4 */

#define RTMP_FEATURE_HTTP	0x01
#define RTMP_FEATURE_ENC	0x02
#define RTMP_FEATURE_SSL	0x04
#define RTMP_FEATURE_MFP	0x08	/* not yet supported */
#define RTMP_FEATURE_WRITE	0x10	/* publish, not play */
#define RTMP_FEATURE_HTTP2	0x20	/* server-side rtmpt */

#define RTMP_PROTOCOL_UNDEFINED	-1
#define RTMP_PROTOCOL_RTMP      0
#define RTMP_PROTOCOL_RTMPE     RTMP_FEATURE_ENC
#define RTMP_PROTOCOL_RTMPT     RTMP_FEATURE_HTTP
#define RTMP_PROTOCOL_RTMPS     RTMP_FEATURE_SSL
#define RTMP_PROTOCOL_RTMPTE    (RTMP_FEATURE_HTTP|RTMP_FEATURE_ENC)
#define RTMP_PROTOCOL_RTMPTS    (RTMP_FEATURE_HTTP|RTMP_FEATURE_SSL)
#define RTMP_PROTOCOL_RTMFP     RTMP_FEATURE_MFP

#define RTMP_DEFAULT_CHUNKSIZE	128

/* needs to fit largest number of bytes recv() may return */
#define RTMP_BUFFER_CACHE_SIZE (16*1024)

#define	RTMP_CHANNELS	65600



/*      RTMP_PACKET_TYPE_...                0x00 */
#define RTMP_PACKET_TYPE_CHUNK_SIZE         0x01
/*      RTMP_PACKET_TYPE_...                0x02 */
#define RTMP_PACKET_TYPE_BYTES_READ_REPORT  0x03
#define RTMP_PACKET_TYPE_CONTROL            0x04
#define RTMP_PACKET_TYPE_SERVER_BW          0x05
#define RTMP_PACKET_TYPE_CLIENT_BW          0x06
/*      RTMP_PACKET_TYPE_...                0x07 */
#define RTMP_PACKET_TYPE_AUDIO              0x08
#define RTMP_PACKET_TYPE_VIDEO              0x09
/*      RTMP_PACKET_TYPE_...                0x0A */
/*      RTMP_PACKET_TYPE_...                0x0B */
/*      RTMP_PACKET_TYPE_...                0x0C */
/*      RTMP_PACKET_TYPE_...                0x0D */
/*      RTMP_PACKET_TYPE_...                0x0E */
#define RTMP_PACKET_TYPE_FLEX_STREAM_SEND   0x0F
#define RTMP_PACKET_TYPE_FLEX_SHARED_OBJECT 0x10
#define RTMP_PACKET_TYPE_FLEX_MESSAGE       0x11
#define RTMP_PACKET_TYPE_INFO               0x12
#define RTMP_PACKET_TYPE_SHARED_OBJECT      0x13
#define RTMP_PACKET_TYPE_INVOKE             0x14
/*      RTMP_PACKET_TYPE_...                0x15 */
#define RTMP_PACKET_TYPE_FLASH_VIDEO        0x16

#define RTMP_MAX_HEADER_SIZE 18

//这个是不是fmt啊
#define RTMP_PACKET_SIZE_LARGE    0
#define RTMP_PACKET_SIZE_MEDIUM   1
#define RTMP_PACKET_SIZE_SMALL    2
#define RTMP_PACKET_SIZE_MINIMUM  3


#define RTMP_LF_AUTH	0x0001	/* using auth param */
#define RTMP_LF_LIVE	0x0002	/* stream is live */
#define RTMP_LF_SWFV	0x0004	/* do SWF verification */
#define RTMP_LF_PLST	0x0008	/* send playlist before play */
#define RTMP_LF_BUFX	0x0010	/* toggle stream on BufferEmpty msg */
#define RTMP_LF_FTCU	0x0020	/* free tcUrl on close */
#define RTMP_LF_FAPU	0x0040	/* free app on close */


//下面这几个新版本里面没有了
#define RTMP_PUB_NAME   0x0001  /* send login to server */
#define RTMP_PUB_RESP   0x0002  /* send salted password hash */
#define RTMP_PUB_ALLOC  0x0004  /* allocated data for new tcUrl & app */
#define RTMP_PUB_CLEAN  0x0008  /* need to free allocated data for newer tcUrl & app at exit */
#define RTMP_PUB_CLATE  0x0010  /* late clean tcUrl & app at exit */