#include <cstdio>
#include <cstdlib>
#include <pcap.h>
#include <stdlib.h>


void usage() {
	printf("syntax: send-arp-test <interface>\n");
	printf("sample: send-arp-test wlan0\n");
}
int check_arg(int argc, char*argv){
	if(argc != 2){
		usage();
		return EXIT_FAILURE;
	}
	return EXIT_SUCCESS;
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



	printf("gh");

	pcap_close(pcap);
}
