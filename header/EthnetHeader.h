#ifndef _ETHNET_HEADER_H_
#define _ETHNET_HEADER_H_
#include"../common/common.h"
#pragma pack(1)
struct EthnetHeader{
  //std::array<char,ETHNET_ADDR_LEN> _destAddr;
  //std::array<char,ETHNET_ADDR_LEN> _srcAddr;

  unsigned char _destAddr[ETHNET_ADDR_LEN];
  unsigned char _srcAddr[ETHNET_ADDR_LEN];
  unsigned short _protoType;
};
#pragma pack()
#endif