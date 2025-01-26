#ifndef PACKETS_H
#define PACKETS_H


typedef struct Packet{
    unsigned long long id;  //8         0
    float fill_level;       //4         8
    float temp;             //4         12
    float humidity;         //4         16
}Packet;

void get_Packet(Packet *packet);

#endif