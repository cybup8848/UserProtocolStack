#include"ProtocolStack.h"
int str2mac(unsigned char *res,char *macAddr){
  std::array<unsigned char,ETHNET_ADDR_LEN>res;
  int index=0;
  
  const char *delimeter=":";
  char *p=strtok(macAddr,delimeter);
  int index=0;
  while(p!=nullptr){
    try{
      res[index++]=static_cast<unsigned char>(std::stoi(p,0,16));
    }catch(std::invalid_argument &ex){
      std::cout<<"Invalid Argument"<<std::endl;
      return 0;
    }catch(std::out_of_range &ex){
      std::cout<<"Out Of Range"<<std::endl;
      return 0;
    }catch(...){
      std::cout<<"Something else"<<std::endl;
      return 0;
    }
    p=strtok(nullptr,delimeter);
  }
  return 1;
}

unsigned int genCheckSum(unsigned short *addr,int len){
  int size=sizeof(unsigned short);
  unsigned int checkSum=0;
  while(len>1){
    checkSum+=ntohs(*addr);
    ++addr;
    len-=size;
  }

  if(len){//为奇数
    unsigned short tmp=ntohs(*(reinterpret_cast<unsigned char *>(addr)));
    checkSum+=(tmp<<8);
  }

  checkSum=(checkSum>>16)+(checkSum&0xffff);
  
  checkSum+=checkSum>>16;//如果有溢出
  return (unsigned short)(~checkSum);
} 

IcmpPackage genEchoIcmpPackage(IcmpPackage *icmpPackage){
  IcmpPackage res;
  memcpy(&res,icmpPackage,sizeof(IcmpPackage));

  //设置ethnet头
  memcpy(res._ethnetHeader._destAddr,
    icmpPackage->_ethnetHeader._srcAddr,ETHNET_ADDR_LEN);
  memcpy(res._ethnetHeader._srcAddr,
    icmpPackage->_ethnetHeader._destAddr,ETHNET_ADDR_LEN);
  res._ethnetHeader._protoType=icmpPackage->_ethnetHeader._protoType;

  //设置ip地址
  res._ipHeader._destIPAddr=icmpPackage->_ipHeader._srcIPAddr;
  res._ipHeader._srcIPAddr=icmpPackage->_ipHeader._destIPAddr;
  
  //设置icmp报文
  res._icmpHeader._type=0x00;//0表示icmp响应、回应报文，8表示icmp请求报文
  res._icmpHeader._code=0x00;
  res._icmpHeader._checkSum=0x0000;
  res._icmpHeader._checkSum=htons(genCheckSum(
    reinterpret_cast<unsigned short *>(&(res._icmpHeader)),sizeof(IcmpHeader)));
  
  return res;
}

ArpPackage genEchoArpPackage(ArpPackage *arpPackage,std::string macAddr){
  ArpPackage res;
  memcpy(&res,arpPackage,sizeof(ArpPackage));
  
  //设置ethnet mac地址
  memcpy(res._ethnetHeader._destAddr,
    arpPackage->_ethnetHeader._srcAddr,ETHNET_ADDR_LEN);
  str2mac(res._ethnetHeader._srcAddr,(char *)(macAddr.c_str()));
  res._ethnetHeader._protoType=arpPackage->_ethnetHeader._protoType;
  
  //设置arp mac地址
  memcpy(res._arpHeader._destMacAddr,
    arpPackage->_arpHeader._srcMacAddr,ETHNET_ADDR_LEN);
  memcpy(res._arpHeader._srcMacAddr,res._ethnetHeader._srcAddr,ETHNET_ADDR_LEN);
  //可以替换为：str2mac(res._arpHeader._srcMacAddr,(char *)(macAddr.c_str()));

  //设置arp ip地址
  res._arpHeader._destIPAddrr=arpPackage->_arpHeader._srcIPAddr;
  res._arpHeader._srcIPAddr=arpPackage->_arpHeader._destIPAddrr;

  //设置oper操作标志
  res._arpHeader._hardwareAddrLen=6;
  res._arpHeader._protocolAddrLen=4;
  res._arpHeader._oper=htons(2);

  return res;
}

UdpPackage genEchoUdpPackage(UdpPackage *arpPackage){
  UdpPackage res;
  memcpy(&res,arpPackage,sizeof(UdpPackage));
  //设置ethnet header
  memcpy(res._ethnetHeader._destAddr,arpPackage->_ethnetHeader._srcAddr,ETHNET_ADDR_LEN);
  memcpy(res._ethnetHeader._srcAddr,arpPackage->_ethnetHeader._destAddr,ETHNET_ADDR_LEN);

  //设置ip header
  res._ipHeader._destIPAddr=arpPackage->_ipHeader._srcIPAddr;
  res._ipHeader._srcIPAddr=arpPackage->_ipHeader._destIPAddr;

  //设置udp header
  res._udpHeader._destPort=arpPackage->_udpHeader._srcPort;
  res._udpHeader._srcPort=arpPackage->_udpHeader._destPort;
  return res;
} 








