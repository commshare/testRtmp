class CRTMPStream  
{  
    public:  
    CRTMPStream(void);  
    ~CRTMPStream(void);  
    public:  
    // 连接到RTMP Server  
    bool Connect(const char* url);  
    // 断开连接  
    void Close();  
    // 发送MetaData  
    bool SendMetadata(LPRTMPMetadata lpMetaData);  
    // 发送H264数据帧  
    bool SendH264Packet(unsigned char *data,unsigned int size,bool bIsKeyFrame,unsigned int nTimeStamp);  
    // 发送H264文件  
    bool SendH264File(const char *pFileName);  
//...  
}  
