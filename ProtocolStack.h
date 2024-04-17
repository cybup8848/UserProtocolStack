#ifndef _PROTOCOL_STACK_H_
#define _PROTOCOL_STACK_H_
#include<array>
#include<string>
#include<stdexcept>
#include<iostream>
#include<unistd.h>
#include<cstring>

#include<arpa/inet.h>


#include"header/ArpPackage.h"
#include"header/IcmpPackage.h"
#include"header/UdpPackage.h"
#include"common/common.h"

int str2mac(unsigned char *res,char *macAddr);
unsigned int genCheckSum(unsigned short *addr,int len);
IcmpPackage genEchoIcmpPackage(IcmpPackage *icmpPackage);
ArpPackage genEchoArpPackage(ArpPackage *arpPackage,std::string macAddr);
UdpPackage genEchoUdpPackage(UdpPackage *arpPackage);


#endif