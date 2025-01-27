#include "packets.h"
#include <memory.h>

/*
long long to bytes
*/
void ll_to_byte(unsigned long long n,unsigned char *bytes) //Little Endian
{
    memcpy(bytes,&n,sizeof(long long));
}

/*
bytes to long long
*/
unsigned long long byte_to_ll(const char * bytes)//Little Endian
{
    unsigned long long num;
    memcpy(&num,bytes,sizeof(long long));
    return num;
}

/*
float to bytes
*/
void float_to_byte(float n,unsigned char *bytes) //Little Endian
{
    memcpy(bytes,&n,sizeof(float));
}

/*
bytes to float
*/
float byte_to_float(const char * bytes)//Little Endian
{
    float num;
    memcpy(&num,bytes,sizeof(float));
    return num;
}

/*
This function takes a packet struct and makes a Buffer from it, that can be sent over to the server
*/
void make_buffer_from_packet(Packet *packet,unsigned char *Buff,int BuffLen)
{
    if(BuffLen<sizeof(Packet)){
        return;
    }

    ll_to_byte(packet->id,Buff);
    float_to_byte(packet->fill_level,Buff+8);
    float_to_byte(packet->temp,Buff+12);
    float_to_byte(packet->humidity,Buff+16);

}