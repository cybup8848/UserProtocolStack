#ifndef _ARP_PACKAGE_H_
#define _ARP_PACKAGE_H_
#include"EthnetHeader.h"
#include"ArpHeader.h"
#pragma pack(1)
struct ArpPackage{
  EthnetHeader _ethnetHeader;
  ArpHeader _arpHeader;
};
#pragma pack()
#endif