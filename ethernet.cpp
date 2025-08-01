#include "ethernet.h"
#include <stdio.h>
#include <string>


using namespace std;

string get_command_output(string command){
    string result;
    FILE *stream;
    uint8_t BUF_SIZE = 128;
    char buffer[BUF_SIZE];

    stream = popen(command.c_str(), "r");
    if(stream){
        while(fgets(buffer, BUF_SIZE, stream) != NULL){
            result.append(buffer);
        }
        return result;

    }
    pclose(stream);
    return "-1";
}

string get_my_mac(char* interface){
    string if_ = interface;

    string command =  "cat /sys/class/net/" + if_ + "/address";
    string result = get_command_output(command);
    // printf("%s", result.c_str());
    return result;
}
