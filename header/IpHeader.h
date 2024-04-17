#ifndef IP_HEADER_H_
#define IP_HEADER_H_
//Total Length：该字段表示整个ip报文的长度，单位是1字节。 
//IP数据报（首部+数据）整体占多少字节。该字段为16位，
//所以数据报最大长度为 2^16−1=65535字节。不过由于链路层的MTU限制。
//超过1480字节后就会被分片（以太帧MTU为1500的情况下，除去20字节的包头）
#pragma pack(1)
struct IpHeader{
  unsigned char _version:4;
  unsigned char _headerLen:4;
  unsigned char _tos;
  unsigned short _totalLen;
  unsigned short _id;
  unsigned short _flag:3;
  unsigned short _offset:13;
  unsigned char _ttl;
  unsigned char _protocol;
  unsigned short _headerCheckSum;
  unsigned int _srcIPAddr;
  unsigned int _destIPAddr;
};
#pragma pack()
#endif