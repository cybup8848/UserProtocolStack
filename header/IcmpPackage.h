#ifndef _ICMP_PACKAGE_H_
#define _ICMP_PACKAGE_H_
#include "EthnetHeader.h"
#include"IpHeader.h"
#include"IcmpHeader.h"
#pragma pack(1)
struct IcmpPackage {
  EthnetHeader _ethnetHeader;
  IpHeader _ipHeader;
  IcmpHeader _icmpHeader;
};
#pragma pack()
#endif