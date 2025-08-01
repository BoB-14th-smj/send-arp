#include "arp.h"
#include "ethernet.h"
#include <netinet/in.h>

using namespace std;

void construct_arp_packet(Ethernet* ethernet, Arp* arp){


}

uint32_t stoi_ip(std::string ip){
    uint32_t result = 0;
    for(int i=0;i<4;i++){
        std::string byte = ip.substr(i*4, 3);
        result = std::stoi(byte.c_str(), nullptr, 16);
        result  = result << 8;
    }
    printf("%x", result);
    return result;

}

string get_my_ip(char* interface){
    string if_ = interface;

    string command =  "hostname -I";
    string result = get_command_output(command);
    size_t index = result.find(" ");
    string final = result.substr(0, index);
    // printf("%s", final.c_str());
    return final;
}

