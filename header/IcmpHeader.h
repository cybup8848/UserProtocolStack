#ifndef _ICMP_HEADER_H_
#define _ICMP_HEADER_H_
#pragma pack(1)
struct IcmpHeader{
  unsigned char _type;
  unsigned char _code;
  unsigned short _checkSum;
  unsigned short _id;
  unsigned short _seq;
  unsigned char _mask[32];//子网掩码
};
#pragma pack()
#endif

