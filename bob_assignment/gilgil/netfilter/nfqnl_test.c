
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <netinet/in.h>
#include <linux/types.h>
#include <linux/netfilter.h>		/* for NF_ACCEPT */
#include <errno.h>
#include <string.h> 			/* for strcpy */

#include <libnetfilter_queue/libnetfilter_queue.h>

#define TYPE_IP 0x0800
#define TYPE_TCP 0x06

unsigned char *black;

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
    unsigned short len; /*ip header length*/
    unsigned short id; /*identification*/
    unsigned short offset;

    uint8_t ttl; /*time to live*/
    uint8_t protocol;
    unsigned short chksum;
    struct in_addr src_ip, dst_ip;
};
struct mytcp{
    uint16_t dst_port;
    uint16_t src_port;
    unsigned long seq_num; /*sequence number*/
    unsigned long ack_num; /*acknowledgment number*/
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
    unsigned short window; /*window*/
    unsigned short chksum; /*checksum*/
    unsigned short ptr; /*urgent pointer*/
};

void dump(unsigned char* buf, int size) {
	int i;
	for (i = 0; i < size; i++) {
		if (i % 16 == 0)
			printf("\n");
		printf("%02x ", buf[i]);
	}printf("\n");
}

/* returns packet id */
static u_int32_t print_pkt (struct nfq_data *tb)
{
	int id = 0;
	struct nfqnl_msg_packet_hdr *ph;
	struct nfqnl_msg_packet_hw *hwph;
	u_int32_t mark,ifi; 
	int ret;
	unsigned char *data;

	ph = nfq_get_msg_packet_hdr(tb);
	if (ph) {
		id = ntohl(ph->packet_id);
		printf("hw_protocol=0x%04x hook=%u id=%u ",
			ntohs(ph->hw_protocol), ph->hook, id);
	}

	hwph = nfq_get_packet_hw(tb);
	if (hwph) {
		int i, hlen = ntohs(hwph->hw_addrlen);

		printf("hw_src_addr=");
		for (i = 0; i < hlen-1; i++)
			printf("%02x:", hwph->hw_addr[i]);
		printf("%02x ", hwph->hw_addr[hlen-1]);
	}

	mark = nfq_get_nfmark(tb);
	if (mark)
		printf("mark=%u ", mark);

	ifi = nfq_get_indev(tb);
	if (ifi)
		printf("indev=%u ", ifi);

	ifi = nfq_get_outdev(tb);
	if (ifi)
		printf("outdev=%u ", ifi);
	ifi = nfq_get_physindev(tb);
	if (ifi)
		printf("physindev=%u ", ifi);

	ifi = nfq_get_physoutdev(tb);
	if (ifi)
		printf("physoutdev=%u ", ifi);

	ret = nfq_get_payload(tb, &data);
	if (ret >= 0)
		printf("payload_len=%d ", ret);
	//dump(data,ret);
	fputc('\n', stdout);

	return id;
}
	

static int cb(struct nfq_q_handle *qh, struct nfgenmsg *nfmsg,
	      struct nfq_data *nfa, void *data)
{
	unsigned char *ipdata;
	int len = 0;
	u_int32_t id = print_pkt(nfa);
	len = nfq_get_payload(nfa, &ipdata);//for payload data and size
	
	/*
	 *for easy to access, I use my own struct when I used in pcaptest assignment
	 *myip struct for TCP protocol
	 *mytcp struct for destinationd port
	*/
	struct myip *myiph = (struct myip*)ipdata;
	ipdata += sizeof(struct myip);
	len -= sizeof(struct myip);

	if(myiph->protocol != TYPE_TCP){
		printf("%x not TCP packet!\n", myiph->protocol);
		return nfq_set_verdict(qh, id, NF_ACCEPT, 0, NULL);
	}
	
	struct mytcp *mytcph = (struct mytcp*)ipdata;
	ipdata += sizeof(struct mytcp);
	len -= sizeof(struct mytcp);
	
	if(mytcph->dst_port != 0x5000){	
		printf("%x not http packet!\n", mytcph->dst_port);
		return nfq_set_verdict(qh, id, NF_ACCEPT, 0, NULL);
	}
	//dump(ipdata, len);
	
	//flag variablel for check if there is black entry
	int flag = 0; 
	for(int i =0; i<len; i++){
		flag = 0;//init for next value 
		for(int j = 0; j < sizeof(black); j++){
			if(black[j] != ipdata[i+j]){
				flag = 1; //if not match, break and research
				break;
			}
		}
	}
	//flag ==1 means there is not black entry
	if(flag==1)
		return nfq_set_verdict(qh,id,NF_ACCEPT,0,NULL);

	//otherwise there is black entry named by print
	printf("\x1b[34mBlock this web site : %s\n\x1b[0m", black);
	return nfq_set_verdict(qh, id, NF_DROP, 0, NULL);//so drop
}

int main(int argc, char **argv)
{
	struct nfq_handle *h;
	struct nfq_q_handle *qh;
	struct nfnl_handle *nh;
	int fd;
	int rv;
	char buf[4096] __attribute__ ((aligned));	
	
	/*argv[2] is black entry, for check black entry in function
	 *copy the string to global variable
	*/
	black = (unsigned char*)malloc(sizeof(argv[2]));
	strcpy(black, argv[2]);

	//below area is same with original
	printf("opening library handle\n");
	h = nfq_open();
	if (!h) {
		fprintf(stderr, "error during nfq_open()\n");
		exit(1);
	}

	printf("unbinding existing nf_queue handler for AF_INET (if any)\n");
	if (nfq_unbind_pf(h, AF_INET) < 0) {
		fprintf(stderr, "error during nfq_unbind_pf()\n");
		exit(1);
	}

	printf("binding nfnetlink_queue as nf_queue handler for AF_INET\n");
	if (nfq_bind_pf(h, AF_INET) < 0) {
		fprintf(stderr, "error during nfq_bind_pf()\n");
		exit(1);
	}

	printf("binding this socket to queue '0'\n");
	qh = nfq_create_queue(h,  0, &cb, NULL);
	if (!qh) {
		fprintf(stderr, "error during nfq_create_queue()\n");
		exit(1);
	}

	printf("setting copy_packet mode\n");
	if (nfq_set_mode(qh, NFQNL_COPY_PACKET, 0xffff) < 0) {
		fprintf(stderr, "can't set packet_copy mode\n");
		exit(1);
	}

	fd = nfq_fd(h);

	for (;;) {
		if ((rv = recv(fd, buf, sizeof(buf), 0)) >= 0) {
			printf("pkt received\n");
			nfq_handle_packet(h, buf, rv);
			continue;
		}
		/* if your application is too slow to digest the packets that
		 * are sent from kernel-space, the socket buffer that we use
		 * to enqueue packets may fill up returning ENOBUFS. Depending
		 * on your application, this error may be ignored. Please, see
		 * the doxygen documentation of this library on how to improve
		 * this situation.
		 */
		if (rv < 0 && errno == ENOBUFS) {
			printf("losing packets!\n");
			continue;
		}
		perror("recv failed");
		break;
	}

	printf("unbinding from queue 0\n");
	nfq_destroy_queue(qh);

#ifdef INSANE
	/* normally, applications SHOULD NOT issue this command, since
	 * it detaches other programs/sockets from AF_INET, too ! */
	printf("unbinding from AF_INET\n");
	nfq_unbind_pf(h, AF_INET);
#endif

	printf("closing library handle\n");
	nfq_close(h);

	exit(0);
}
