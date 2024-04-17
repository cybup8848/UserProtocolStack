#ifndef _ARP_HEADER_H_
#define _ARP_HEADER_H_
#include"../common/common.h"
#pragma pack(1)
struct ArpHeader{
  unsigned short _hardwareType;
  unsigned short _protocolType;
  unsigned char _hardwareAddrLen;
  unsigned char _protocolAddrLen;
  unsigned short _oper;//请求为1，回复为2
  unsigned char _srcMacAddr[ETHNET_ADDR_LEN];
  unsigned int _srcIPAddr;
  unsigned char _destMacAddr[ETHNET_ADDR_LEN];
  unsigned int _destIPAddrr;
};
#pragma pack()
#endif