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

void get_Buffer(Packet *packet,char Buff[1024],int BuffLen)
{
    if(BuffLen<sizeof(Packet)){
        return;
    }



}