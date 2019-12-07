/*
 * @file CRtmpStream.cpp
 * @author Akagi201
 * @date 2015/02/10
 */

#include <unistd.h>
#include"lwlog/lwlog.h"

#include "CRtmpStream.h"
#include "bytestream.h"
#include<iostream>
using namespace std;

char *put_byte(char *output, uint8_t nVal) {
    output[0] = nVal;

    return output + 1;
}

/*
°ÑÒ»¸öÕ¼ÓÃÁËÁ½¸ö×Ö½ÚµÄÊý¾Ý£¬µÍ°ËÎ»´æÔÚ»º³åµÄ¸ßµØÖ·£¬¸ß°ËÎ»´æÔÚµÍµØÖ·¡£
Èç¹û»º³å´ú±íµÄÊÇÐ¡¶Ë´æ´¢£¬ÄÇÃ´ÊäÈëµÄÊý¾ÝÊÇ´ó¶ËÄ£Ê½µÄ¡£
ÄÇÕâ¸öÊµ¼ÊÉÏÊÐ´ó¶Ë×ªÐ¡¶Ëå
*/
char *put_be16(char *output, uint16_t nVal) {
    output[1] = nVal & 0xff;
    output[0] = nVal >> 8;

    return output + 2;
}

char *put_be24(char *output, uint32_t nVal) {
    output[2] = nVal & 0xff;
    output[1] = nVal >> 8;
    output[0] = nVal >> 16;

    return output + 3;
}

char *put_be32(char *output, uint32_t nVal) {
    output[3] = nVal & 0xff;
    output[2] = nVal >> 8;
    output[1] = nVal >> 16;
    output[0] = nVal >> 24;

    return output + 4;
}

char *put_be64(char *output, uint64_t nVal) {
    output = put_be32(output, nVal >> 32);
    output = put_be32(output, nVal);

    return output;
}

char *put_amf_string(char *c, const char *str) {
    uint16_t len = strlen(str);
    c = put_be16(c, len);
    memcpy(c, str, len);

    return c + len;
}

CRtmpStream::CRtmpStream(void) : m_pRtmp(NULL) {
    m_pRtmp = RTMP_Alloc();
    RTMP_Init(m_pRtmp);

    m_pFid = NULL;
    m_nDstSocket = -1;

    return;
}

CRtmpStream::~CRtmpStream(void) {
    return;
}

bool CRtmpStream::Connect(const char *url) {
    if (RTMP_SetupURL(m_pRtmp, (char *) url) < 0) {
        return FALSE;
    }

    RTMP_EnableWrite(m_pRtmp);

    if (RTMP_Connect(m_pRtmp, NULL) < 0) {
        return FALSE;
    }

    m_nDstSocket = m_pRtmp->m_sb.sb_socket;

    if (RTMP_ConnectStream(m_pRtmp, 0) < 0) {
        return FALSE;
    }

    return TRUE;
}

void CRtmpStream::Close(void) {
    if (m_pRtmp) {
        RTMP_Close(m_pRtmp);
        RTMP_Free(m_pRtmp);
        m_pRtmp = NULL;
    }

    if (m_pFid) {
        fclose(m_pFid);
        m_pFid = NULL;
    }

    return;
}

/*
 * @brief »ñÈ¡flvÎÄ¼þÍ·Êý¾Ý, °üÀ¨metadataÊý¾ÝºÍÆäºóµÄprevious tag size, ·µ»ØÎÄ¼þÍ·×Ö½Ú´óÑ§
 */
int CRtmpStream::GetFlvHeader(unsigned char *buf) {
    // ¶ÁÈ¡flvÎÄ¼þÍ·9 + 4
    fread(buf, 13, 1, m_pFid);
     int i=0;
     /*http://smartgeek.iteye.com/blog/1543825
     hh ½«»á½« int ×ª»¯³É char£»unsigned int ×ª»¯³É unsigned char */
     for(i=0;i<13;i++){
        printf( "the hex value of a is 0x%02hhx\n", buf[i] );
     }
     /*11¸ö×Ö½ÚµÄtag headerÐÅÏ¢£¬
ÆäÖÐ Tag HeaderÓÉ11¸ö×Ö½Ú×é³É£º

µÚ1¸ö×Ö½Ú£º±íÊ¾ÀàÐÍ£¬0x08±íÊ¾ÒôÆµ£¬0x09±íÊ¾ÊÓÆµ£¬0x12±íÊ¾Script Data£»
µÚ2-4×Ö½Ú£º±íÊ¾µ±Ç°Tag DataµÄ³¤¶È£»
µÚ5-7×Ö½Ú£º±íÊ¾TagµÄÊ±¼ä´Á£¬ÒÔºÁÃëÎªµ¥Î»£»
µÚ8×Ö½Ú£ºÊ±¼ä´ÁµÄÀ©Õ¹×Ö½Ú£¬ÓÃÓÚÀ©³äÉÏÃæµÄÊ±¼ä´Á£»
µÚ9-11×Ö½Ú£º±íÊ¾Stream ID£¬×ÜÎª0¡£

     */
    // ¶ÁÈ¡tag header
    fread(buf + 13, 11, 1, m_pFid);

    /*ox12,´ú±íµÚÒ»¸ötagÊÇMetadataTag*/
    unsigned char type = buf[13];
    printf( "the hex value of type is 0x%02hhx\n", type );

    /*ÕâÓ¦¸Ã¾Í¿ÉÒÔËµÃ÷FLVÎÄ¼þ´æ´¢Êý¾ÝÊÇ°´ÕÕ´ó¶ËÀ´´æ´¢µÄ£¬ÒòÎªÄÚ´æµÍµØÖ·£¬´æ·ÅµÄÊÇ¸ßÎ»Êý¾Ý
            http://www.oschina.net/translate/understanding-big-and-little-endian-byte-order
            sizeÊÇÕ¼ÁËÈý¸ö×Ö½ÚµÄ
    */
    unsigned int size = (unsigned char) buf[14] * 256 * 256 + (unsigned char) buf[15] * 256 + (unsigned char) buf[16];
    printf("metadata size[%d]\n",size);
    // ¶ÁÈ¡metadataÊý¾Ý, °üÀ¨ÆäºóµÄprevious tag size
    if (0x12 == type) { /*0x12±íÊ¾Script Data*/
        fread(buf + 24, size + 4, 1, m_pFid);
        return size + 24 + 4;
    } else {
        printf("The first tag is not metadata tag!\n");
        return -1;
    }
}

/*
 * @brief ¶ÁÈ¡Ò»Ö¡flvÊý¾Ýµ½bufÖÐ, °üÀ¨ÆäºóµÄprevious tag size
 */
int CRtmpStream::GetFlvFrame(unsigned char *buf) {
    unsigned int framesize = 0;
    unsigned int bodysize = 0;
    static int tagIndex = 0;

    // ¶ÁÈ¡tag header
    fread(buf, 11, 1, m_pFid);
    framesize += 11;

    // »ñÈ¡tagµÄÀàÐÍ
    unsigned char type = buf[0];
    if ((0x08 == type) || (0x09 == type)) {
        ++tagIndex;
    } else {
        printf("Error while reading flv frame!\n");
        return -1;
    }

    // »ñÈ¡bodysize
    bodysize = (unsigned char) buf[1] * 256 * 256 + (unsigned char) buf[2] * 256 + (unsigned char) buf[3];
    fread(buf + 11, bodysize, 1, m_pFid);
    framesize += bodysize;
    printf("\n%s Tag%d Size: %d\n", (type == 0x08) ? "Audio" : ((type == 0x09) ? "Video" : "Metadata"), tagIndex, framesize);

    // ½«4¸ö×Ö½ÚµÄprevious size¶ÁÈ¡µ½bufÖÐ
    fread(buf + framesize, 4, 1, m_pFid);
    framesize += 4;

    return framesize;
}

/*
 * @brief ·¢ËÍflvÎÄ¼þÍ·
 */
int CRtmpStream::SendFlvHeader(unsigned char *buf, int size) {

    uint32_t timestamp;
    int ret = 0;
    int pktSize, pktType;
    unsigned char *pHeader = buf + 13;

    // »ñÈ¡metadata tagµÄÍ·ÐÅÏ¢(11¸ö×Ö½Ú)¡¢
    /*
type                Ò»¸ö×Ö½Ú  18
data size          Èý¸ö×Ö½Ú   397
timestamp         ËÄ¸ö×Ö½Ú      0
streamid          Èý¸ö×Ö½Ú     0
    */
    pktType = bytestream_get_byte((const unsigned char **) &pHeader);

    lwlog_info("pktType[%d]", pktType);
    pktSize = bytestream_get_be24((const unsigned char **) &pHeader);
    lwlog_info("pktSize[%d]", pktSize);
    timestamp = bytestream_get_be24((const unsigned char **) &pHeader);
    lwlog_info("#1#timestamp[%d]", timestamp);
    timestamp |= bytestream_get_byte((const unsigned char **) &pHeader) << 24;
    lwlog_info("#2#timestamp[%d]", timestamp);
    bytestream_get_be24((const unsigned char **) &pHeader);
    lwlog_info("okokok");
    // ¹¹ÔìRTMP°ü
    RTMPPacket packet;
    RTMPPacket_Reset(&packet);
    ret = RTMPPacket_Alloc(&packet, size + 16);
    if (!ret) {
        lwlog_err("RTMPPacket_Alloc fail");
        return -1;
    }

    packet.m_packetType = pktType;
    packet.m_nBodySize = pktSize + 16;
    packet.m_nTimeStamp = timestamp;
    packet.m_nChannel = 4;
    packet.m_headerType = RTMP_PACKET_SIZE_LARGE;
    packet.m_nInfoField2 = m_pRtmp->m_stream_id;

    uint8_t *body = (uint8_t *) packet.m_body;
    put_amf_string((char *) body, "@setDataFrame");
    memcpy(body, buf + 24, pktSize);

    /*dump for debug*/
    RTMPPacket_Dump(&packet);
    cout<<"before send flvheader pkt "<<endl;
    ret = RTMP_SendPacket(m_pRtmp, &packet, 0);

    return ret;
}

/*
 * @brief ·¢ËÍflvÒ»Ö¡
 */
int CRtmpStream::SendFlvFrame(unsigned char *buf, int size) {
    uint32_t timestamp;
    int ret = 0;
    int pktSize, pktType;
    unsigned char *pHeader = buf;

    // »ñÈ¡tag headerÐÅÏ¢(11¸ö×Ö½Ú)
    pktType = bytestream_get_byte((const unsigned char **) &pHeader);
    pktSize = bytestream_get_be24((const unsigned char **) &pHeader);
    timestamp = bytestream_get_be24((const unsigned char **) &pHeader);
    timestamp |= bytestream_get_byte((const unsigned char **) &pHeader) << 24;
    bytestream_get_be24((const unsigned char **) &pHeader);

    // ¹¹ÔìRTMP°ü
    RTMPPacket packet;
    RTMPPacket_Reset(&packet);
    ret = RTMPPacket_Alloc(&packet, size);
    if (!ret) {
        return -1;
    }

    packet.m_packetType = pktType;
    packet.m_nBodySize = pktSize;
    packet.m_nTimeStamp = timestamp;
    packet.m_nChannel = 0x04;//4;
    packet.m_headerType = RTMP_PACKET_SIZE_LARGE;
    packet.m_nInfoField2 = m_pRtmp->m_stream_id;

    memcpy(packet.m_body, buf + 11, pktSize);

    ret = RTMP_SendPacket(m_pRtmp, &packet, 0);

    return ret;
};

/*
 * @brief ·¢ËÍflvÎÄ¼þ
 */
bool CRtmpStream::SendFlvFile(const char *filename) {
    int size = 0;
    unsigned char buf[SEND_BUF_SIZE] = {0};

    m_pFid = fopen(filename, "rb");
    if (NULL == m_pFid) {
        printf("Can net open the file: %s\n", filename);
        return FALSE;
    }

    size = GetFlvHeader(buf);
    lwlog_info("flvheader size[%d]",size);
    SendFlvHeader(buf, size);
    lwlog_debug("===========after send flv header================");
    #if 0

    // Ñ­»··¢ËÍÃ¿Ò»Ö¡Êý¾Ý
    while (!feof(m_pFid)) {
        memset(buf, 0, SEND_BUF_SIZE);
        size = GetFlvFrame(buf);
        if (size > 0) {
            /*Ñ­»··¢ËÍflvµÄÊý¾ÝÖ¡*/
            SendFlvFrame(buf, size);
            sleep(40);
        }
    }
    #endif
    return TRUE;
}
