#ifndef _UDP_HEADER_H_
#define _UDP_HEADER_H_
#pragma pack(1)
//长度：是指UDP头部和UDP数据的字节长度。因为UDP头 部长度为8字节，
//所以该字段的最小值为8。
struct UdpHeader{
  unsigned short _srcPort;
  unsigned short _destPort;
  unsigned short _udpLen;
  unsigned short _udpCheckSum;
};
#pragma pack()
#endif


