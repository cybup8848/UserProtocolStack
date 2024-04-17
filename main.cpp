#define NETMAP_WITH_LIBS//需要开启netmap的宏

#include<sys/poll.h>
#include<net/netmap_user.h>

#include"ProtocolStack.h"

/*nm_open主要做了两个事情：

把网卡的内存映射到内存；

把fd指向eth0对应的设备文件。

通过检测fd，就可以判断网卡是否有数据，有数据就可以直接操作内存。
*/

//nm_nextpkt是操作内存，取出来的就是一个完整的包。

int main(int argc,char *argv[]){
  struct nm_pkthdr h;//ringbuff的指针
  struct nm_desc *nmr=nm_open("netmap:ethn1",nullptr,0,nullptr);
  if(!nmr){
    return -1;
  }

  struct pollfd pfd={0};
  pfd.fd=nmr->fd;//监听这个文件描述符
  pfd.events=POLLIN;
  
  for(;;){
    int cn=poll(&pfd,1,0);
    if(cn<=0){
      continue;
    }
    if(pfd.events&POLLIN){//读事件发生
      unsigned char *pktStream=nm_nextpkt(nmr,&h);
      EthnetHeader *ethnetHeader=reinterpret_cast<EthnetHeader*>(pktStream);
      if(ntohs(ethnetHeader->_protoType)==PROTO_IP){
        UdpPackage *udpPackage=reinterpret_cast<UdpPackage *>(pktStream);
        if(ntohs(udpPackage->_ipHeader._protocol)==PROTO_UDP){
          int udpLen=udpPackage->_udpHeader._udpLen;
          udpPackage->_data[udpLen-8]='\0';
          std::cout<<"udp:"<<udpPackage->_data<<std::endl;
          UdpPackage echoUpdPackage=genEchoUdpPackage(udpPackage);
          nm_inject(nmr,&echoUpdPackage,sizeof(UdpPackage));
        } else if(ntohs(udpPackage->_ipHeader._protocol)==PROTO_ICMP){
          IcmpPackage *icmpPackage=reinterpret_cast<IcmpPackage *>(pktStream);
          IcmpPackage echoIcmpPackage=
            genEchoIcmpPackage(icmpPackage);

          //将返回包，发送到网卡的内存，转换为光信号，发送出去
          nm_inject(nmr,&echoIcmpPackage,sizeof(echoIcmpPackage));
        }
      } else if(ethnetHeader->_protoType==PROTO_ARP){
        ArpPackage *arpPackage=reinterpret_cast<ArpPackage *>(pktStream);
        
        //去掉if，就可以进行arp攻击
        if(arpPackage->_arpHeader._destIPAddrr=inet_addr("10.36.121.51")){
          
          ArpPackage echoArpPackage=
            genEchoArpPackage(arpPackage,"fa:16:3e:72:4c:ca");

          //将返回包，发送到网卡的内存，转换为光信号，发送出去
          nm_inject(nmr,&echoArpPackage,sizeof(echoArpPackage));
        }
      }
    }
  }
  return 0;
}













