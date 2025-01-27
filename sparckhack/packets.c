#include "packets.h"
#include "server.h"
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
Gets the next packet which is avalaible, blocks if no packet is avalaible. If multiple packets are avalaible 
then returns the first packet and keeps other packets in queue.
*/
void get_Packet(Packet *packet)
{
    char RecvBuf[1024];
    int BufLen = 1024;

    get_Buffer(RecvBuf,BufLen);
    if(BufLen<16){
        return;
    }

    char temp[8];
    memcpy(temp,RecvBuf,sizeof(long long));
    packet->id = byte_to_ll(temp);
    memcpy(temp,RecvBuf+8,sizeof(float));
    packet->fill_level = byte_to_float(temp);
    memcpy(temp,RecvBuf+12,sizeof(float));
    packet->temp = byte_to_float(temp);
    memcpy(temp,RecvBuf+16,sizeof(float));
    packet->humidity = byte_to_float(temp);

}