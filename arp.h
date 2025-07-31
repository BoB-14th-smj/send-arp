#pragma once
#include <cstdint>
#include <stdint.h>
#include <stdio.h>
#include <netinet/in.h>
#include <string.h>


struct Arp {
private:
    uint16_t h_type;
    uint16_t p_type;

    uint8_t h_length;
    uint8_t p_length;
    uint16_t operaton;

    uint8_t s_mac_[6];
    uint32_t s_ip_;

    uint8_t t_mac_[6];
    uint32_t t_ip_;


public:
    uint16_t get_operation(void) { return operaton; }
    uint8_t* get_smac(void) { return s_mac_; }
    uint8_t* get_tmac(void) { return t_mac_; }
    uint32_t get_sip(void) { return s_ip_; }
    uint32_t get_tip(void) { return t_ip_; }


    void set_smac(uint8_t* smac){
        for (int i=0;i<6;i++){
            s_mac_[i] = smac[i];
        }
    }

    void set_dmac(uint8_t* tmac){
        for (int i=0;i<6;i++){
            t_mac_[i] = tmac[i];
        }
    }

    void set_sip(uint32_t sip){

    }

    void set_tip(uint32_t tip){

    }








}
