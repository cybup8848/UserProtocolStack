#ifndef _UDP_PACKAGE_H_
#define _UDP_PACKAGE_H_
#include"EthnetHeader.h"
#include"IpHeader.h"
#include"UdpHeader.h"
#pragma pack(1)
struct UdpPackage{
  EthnetHeader _ethnetHeader;
  IpHeader _ipHeader;
  UdpHeader _udpHeader;
  unsigned char _data[0];//零长数组
};
#pragma pack()
#endif