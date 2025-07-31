#pragma once
#include <stdint.h>
#include <stdio.h>
#include <netinet/in.h>


//Detail2~3. struct
struct Ethernet {
private:
    uint8_t d_mac_[6];
    uint8_t s_mac_[6];
    uint16_t e_type;

public:
    uint8_t* get_d_mac(void) { return d_mac_; }
    uint8_t* get_s_mac(void) { return s_mac_; }
    uint16_t get_ether_type(void) { return ntohs(e_type); }

};

