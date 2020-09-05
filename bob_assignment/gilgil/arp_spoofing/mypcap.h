#ifndef MYPCAP_H
#define MYPCAP_H
#include <stdint.h>
#include <netinet/in.h>
#include <pcap.h>

#pragma pack(push, 1)
struct packet_addr{
    uint8_t mymac[6];
    uint8_t myip[4];
    uint8_t sender_mac[6];
    uint8_t sender_ip[4];
    uint8_t target_mac[6];
    uint8_t target_ip[4];
    uint8_t broadcast[6]={0xff,0xff,0xff,0xff,0xff,0xff};
    uint8_t unknown[6] = {0x0,0x0,0x0,0x0,0x0,0x0};
};

struct myether{
    uint8_t dst_addr[6];
    uint8_t src_addr[6];
    uint16_t type_id;
};

struct myip{
    /*by byte order*/
#if __BYTE_ORDER__ == __LITTLE_ENDIAN__
    unsigned int hdr_len:4;
    unsigned int hdr_v:4;
#endif
#if __BYTE_ORDER__ == __ORDER_BIG_ENDIAN__
    unsigned int hdr_v:4;
    unsigned int hdr_len:4;
#endif
    uint8_t tos; /*type of services*/
    uint16_t len; /*ip header length*/
    uint16_t id; /*identification*/
    uint16_t offset;

    uint8_t ttl; /*time to live*/
    uint8_t protocol;
    uint16_t chksum;
    struct in_addr src_ip, dst_ip;
};

struct mytcp{
    uint16_t dst_port;
    uint16_t src_port;
    uint64_t seq_num; /*sequence number*/
    uint64_t ack_num; /*acknowledgment number*/
#if __BYTE_ORDER__ == __LITTLE_ENDIAN__
    uint8_t reverse:4;
    uint8_t offset:4;
#endif
#if __BYTE_ORDER__ == __ORDER_BIG_ENDIAN__
    uint8_t offset:4; /*data offset*/
    uint8_t reverse:4;
#endif
    uint8_t flags; /* C E U A P R S F */
#  define TH_FIN    0x01
#  define TH_SYN    0x02
#  define TH_RST    0x04
#  define TH_PUSH   0x08
#  define TH_ACK    0x10
#  define TH_URG    0x20
    uint16_t window; /*window*/
    uint16_t chksum; /*checksum*/
    uint16_t ptr; /*urgent pointer*/
};

struct myarp{
    uint16_t htype;
    uint16_t ptype;
    uint8_t maclen;
    uint8_t protolen;
    uint16_t opcode;
#define apr_req 0x01
#define arp_rep 0x02
#define rarp_req 0x03
#define rarp_rep 0x04
    uint8_t smac[6];
    uint8_t sip[4];
    uint8_t dmac[6];
    uint8_t dip[4];
};
#pragma pack(pop)

void getMacIPAddress(char* interface,uint8_t *mac, uint8_t *ip_addr);
myether make_eth(unsigned char *smac, unsigned char *dmac);
myarp make_arp( int proto, unsigned char *smac, unsigned char *sip, unsigned char *dmac, unsigned char *dip);
unsigned char* make_packet(myether eth, myarp arp, int &len);
bool receive_arp(const unsigned char *packet, unsigned char *tmac, unsigned char *mmac);
void get_arpmac(char* interface, unsigned char* packet,int &len, unsigned char *tmac, unsigned char *mmac);
void arp_injection(int cnt, char* interface,struct packet_addr *ps);
void packet_sniffing(char* interface, struct packet_addr* pt);
int packet_check(const unsigned char *packet,struct packet_addr* pv);
void packet_relay(char* interface, const u_char* r_packet,struct packet_addr* pu, uint32_t len);
#endif // MYPCAP_H
