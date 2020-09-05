#include <pcap.h>
#include <mypcap.h>
#include <net/if.h>
#include <string.h>
#include <sys/ioctl.h>
#include <netinet/in.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <iostream>
#define TYPE_IP 0x0800
#define TYPE_ARP 0x0806

void get_mymac(unsigned char *mymac){
    struct ifreq ifr;
    struct ifconf ifc;
    char buf[1024];
    char ipbuf[40];
    int success = 0;

    int sock = socket(AF_INET, SOCK_DGRAM, IPPROTO_IP);
    if (sock == -1) { printf("socket error\n"); };

    ifc.ifc_len = sizeof(buf);
    ifc.ifc_buf = buf;
    if (ioctl(sock, SIOCGIFCONF, &ifc) == -1) { printf("ioctl error\n"); }

    struct ifreq* it = ifc.ifc_req;
    const struct ifreq* const end = it + (ifc.ifc_len / sizeof(struct ifreq));

    for (; it != end; ++it) {
        strcpy(ifr.ifr_name, it->ifr_name);
        if (ioctl(sock, SIOCGIFFLAGS, &ifr) == 0) {
            if (! (ifr.ifr_flags & IFF_LOOPBACK)) { // don't count loopback
                if (ioctl(sock, SIOCGIFHWADDR, &ifr) == 0) {
                    success = 1;
                    break;
                }
            }
        }
        else { printf("what?"); }
    }

    if (success)   memcpy(mymac, ifr.ifr_hwaddr.sa_data, 6);

    //printf("%x:%x:%x:%x:%x:%x\n",mymac[0],mymac[1],mymac[2],mymac[3],mymac[4],mymac[5]);
}

void make_eth(myether *eth, unsigned char *smac, unsigned char *dmac){

    for(int i =0; i< 6;i++){
        eth->src_addr[i] = smac[i];
        eth->dst_addr[i] = dmac[i];
    }
    eth->type_id = htons(TYPE_ARP);
}

void make_arp(myarp *arp, int proto, unsigned char *smac, unsigned char *sip, unsigned char *dmac, unsigned char *dip){
    for(int i =0 ; i<6 ;i++){
        if(i<4){
            arp->sip[i] = (unsigned char)sip[i];
            arp->dip[i] = (unsigned char)dip[i];
        }
        arp->smac[i] = smac[i];
        arp->dmac[i] = dmac[i];
    }
    arp->opcode = htons(proto);
    arp->htype = htons(0x01);
    arp->ptype = htons(0x0800);
    arp->maclen = 0x06;
    arp->protolen = 0x04;
}

bool receive_arp(const u_char *packet, unsigned char *tmac, unsigned char *mmac){
    //check procotol is "arp"
    struct myether *myeh = (struct myether *)packet;
    packet += sizeof (struct myether);
    unsigned short myether_type = ntohs(myeh->type_id);
    if(myether_type == TYPE_ARP){
        if(memcmp(mmac,myeh->dst_addr,sizeof(mmac))){
            memcpy(tmac, myeh->src_addr, sizeof(tmac));
            //tmac = myeh->src_addr;
            return true;}
    }
}
