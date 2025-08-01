#pragma once
#include <cstdint>
#include <stdint.h>
#include <stdio.h>
#include <netinet/in.h>
#include <string>
#include "ethernet.h"


uint32_t stoi_ip(std::string ip);
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
    Arp();
    Arp(uint8_t* smac, uint8_t* tmac, uint32_t sip, uint32_t tip){
        set_smac(smac);
        set_tmac(tmac);
        set_sip(sip);
        set_tip(tip);
    }
    Arp(std::string smac, std::string tmac, std::string sip, std::string tip){
        set_smac(smac);
        set_tmac(tmac);
        set_sip(sip);
        set_tip(tip);
    }

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

    void set_smac(std::string smac){
        stoi_mac(smac, s_mac_);
    }

    void set_tmac(uint8_t* tmac){
        for (int i=0;i<6;i++){
            t_mac_[i] = tmac[i];
        }
    }

    void set_tmac(std::string tmac){
        stoi_mac(tmac, t_mac_);
    }

    void set_sip(uint32_t sip){
        s_ip_ = ntohl(sip);
    }

    void set_sip(std::string sip){
        s_ip_ = ntohl(stoi_ip(sip));
    }

    void set_tip(uint32_t tip){
        t_ip_ = ntohl(tip);

    }

    void set_tip(std::string tip){
        t_ip_ = ntohl(stoi_ip(tip));
    }

};

struct ArpPacket{
private:
    Ethernet* ethernet;
    Arp* arp;

public:
    ArpPacket();
    ArpPacket(Ethernet* ethernet_, Arp* arp_){
        ethernet = ethernet_;
        arp = arp_;
    };
};


