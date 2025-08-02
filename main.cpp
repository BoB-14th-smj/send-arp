#pragma pack(1)

#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <pcap.h>
#include <pcap/pcap.h>
#include <stdlib.h>
#include "ethernet.h"
#include <string>
#include <sys/types.h>
#include "arp.h"


void usage() {
	printf("syntax : send-arp <interface> <sender ip> <target ip> [<sender ip 2> <target ip 2> ...]\n");
	printf("sample : send-arp wlan0 192.168.10.2 192.168.10.1");


}
int check_arg(int argc, char*argv){
	if(argc < 4 ){
		usage();
		return EXIT_FAILURE;
	}
	else if((argc % 2 != 0)){
		usage();
		return EXIT_FAILURE;
	}
	return EXIT_SUCCESS;
}

void arp_request(pcap_t* pcap, char* dev, std::string d_mac_, std::string s_mac_, char* sender_ip, char* target_ip){
	uint16_t ether_type = 0x0806;

	Ethernet* ethernet = new Ethernet(d_mac_, s_mac_, ether_type);
	// ethernet->print_ethernet();

	std::string my_ip = get_my_ip(dev);
	// printf("\n%s", my_ip.c_str());
	uint16_t op_ = 0x0001;
	Arp* arp = new Arp(s_mac_, d_mac_, my_ip, target_ip, op_);
	// arp->print_arp();
	ArpPacket *packet = new ArpPacket(ethernet, arp);
 //
	if(pcap_sendpacket(pcap, (u_char*)packet , sizeof(*packet)) !=0){
		printf("ERROR");
		exit(1);
	}

}




void attack_arp(int couple, char* dev, char* sender_ip, char* target_ip, pcap_t* pcap){
	//Send Arp Request
	std::string d_mac_  = "ff:ff:ff:ff:ff:ff";
	std::string s_mac_ = get_my_mac(dev);
	std::string my_ip = get_my_ip(dev);
	arp_request(pcap, dev, d_mac_, s_mac_, (char*)my_ip.c_str(), target_ip);




}

int main(int argc, char* argv[]) {
	if(check_arg(argc, *argv)){
		return EXIT_FAILURE;
	}






	char* dev = argv[1];
	char errbuf[PCAP_ERRBUF_SIZE];
	pcap_t* pcap = pcap_open_live(dev, 0, 0, 0, errbuf);
	if (pcap == nullptr) {
		fprintf(stderr, "couldn't open device %s(%s)\n", dev, errbuf);
		return EXIT_FAILURE;
	}

	attack_arp(argc -2 ,dev ,argv[2] , argv[3],  pcap);

	pcap_close(pcap);
}
