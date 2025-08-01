#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <pcap.h>
#include <stdlib.h>
#include "ethernet.h"
#include <string>
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

void arp_request(char* dev, char* sender_ip, char* target_ip){
	std::string d_mac_  = "ff:ff:ff:ff:ff:ff";
	std::string s_mac_ = get_my_mac(dev);
	uint16_t ether_type = 0x0806;

	Ethernet* ethernet = new Ethernet(d_mac_, s_mac_, ether_type);
	ethernet->print_ethernet();

	std::string my_ip = get_my_ip(dev);
	printf("\n%s", my_ip.c_str());
	// Arp* arp = new Arp(d_mac_, s_mac_, sender_ip, target_ip);

}




void attack_arp(int couple, char* dev, char* sender_ip, char* target_ip){
	//Send Arp Request
	arp_request(dev, sender_ip, target_ip);




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

	attack_arp(argc -2 ,dev ,argv[2] , argv[3]);

	pcap_close(pcap);
}
