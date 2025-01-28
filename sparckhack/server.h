
#ifndef SERVER_H
#define SERVER_H

#include "packets.h"

int server_init();
void get_Recv_Buffer(char *RecvBuf,int BufLen);
int server_close();

#endif