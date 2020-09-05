#include <mypcap.h>
#include <pcap.h>
#include <arpa/inet.h>

#define TYPE_IP 0x0800
#define TYPE_TCP 0x06

void print_ether(struct myether *eth){
    printf("\nSource MAC = ");
    for(int i = 0; i < 6 ; i++){
        printf(":%02X", eth->src_addr[i]);
    }
    printf("\nDestination MAC = ");
    for(int i = 0; i < 6 ; i++){
        printf(":%02X", eth->dst_addr[i]);
    }
}
void print_ip(struct myip* ip){
    printf("\nSource address : %s", inet_ntoa(ip->src_ip));
    printf("\nDestination address : %s", inet_ntoa(ip->dst_ip));
}
void print_tcp(struct mytcp* tcp){
    printf("\nSource port : %d", ntohs(tcp->src_port));
    printf("\nDestination port : %d\n", ntohs(tcp->dst_port));
}
void display_packet(const u_char *packet){

    //take ether header
    struct myether *myeh = (struct myether *)packet;
    print_ether(myeh);

    //move for ip header
    packet += sizeof(struct myether);

    //check ethernet type
    unsigned short myether_type = ntohs(myeh->type_id);

    //if there is ip next to ethernet
    if(myether_type == TYPE_IP){

        //take ip header
        struct myip *myiph = (struct myip *)packet;
        print_ip(myiph);

        //if there is tcp next to ip
        if(myiph->protocol == TYPE_TCP){

            //move for tcp header
            packet += sizeof (struct myip);
            //take tcp header
            struct mytcp *mytcph = (struct mytcp *)packet;
            print_tcp(mytcph);

            //print data to 10 bytes
            int length = 0;
            while(length != 10){
                printf("%02X ", *(packet++));
                length++;
            }
            printf("\n");
        }
        else{
            printf("this is not TCP packet!\n");
        }
    }
    else{
        printf("this is not IP packet!\n");
    }
}
