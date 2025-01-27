#ifndef UNICODE
#define UNICODE
#endif

#define WIN32_LEAN_AND_MEAN

#include <winsock2.h>
#include <Ws2tcpip.h>
#include <stdio.h>
#include <math.h>
#include "packets.h"

// Link with ws2_32.lib
#pragma comment(lib, "Ws2_32.lib")

SOCKET SendSocket = INVALID_SOCKET;
struct sockaddr_in RecvAddr;

int client_init()
{
    int iResult;
    WSADATA wsaData;

    unsigned short Port = 27015;

    //----------------------
    // Initialize Winsock
    iResult = WSAStartup(MAKEWORD(2, 2), &wsaData);
    if (iResult != NO_ERROR) {
        wprintf(L"WSAStartup failed with error: %d\n", iResult);
        return 1;
    }

    //---------------------------------------------
    // Create a socket for sending data
    SendSocket = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
    if (SendSocket == INVALID_SOCKET) {
        wprintf(L"socket failed with error: %ld\n", WSAGetLastError());
        WSACleanup();
        return 1;
    }
    //---------------------------------------------
    // Set up the RecvAddr structure with the IP address of
    // the receiver (in this example case "192.168.1.1")
    // and the specified port number.
    RecvAddr.sin_family = AF_INET;
    RecvAddr.sin_port = htons(Port);
    RecvAddr.sin_addr.s_addr = inet_addr("127.0.0.1");

    return iResult;

}

int send_Buffer(char *SendBuf,int BufLen)
{
    int iResult;
    //---------------------------------------------
    // Send a datagram to the receiver
    wprintf(L"Sending a datagram to the receiver...\n");
    iResult = sendto(SendSocket,
                     SendBuf, BufLen, 0, (SOCKADDR *) & RecvAddr, sizeof (RecvAddr));
    if (iResult == SOCKET_ERROR) {
        wprintf(L"sendto failed with error: %d\n", WSAGetLastError());
        closesocket(SendSocket);
        WSACleanup();
        return 1;
    }

    return iResult;
}

int client_close()
{
    int iResult;
    
    //---------------------------------------------
    // When the application is finished sending, close the socket.
    wprintf(L"Finished sending. Closing socket.\n");
    iResult = closesocket(SendSocket);
    if (iResult == SOCKET_ERROR) {
        wprintf(L"closesocket failed with error: %d\n", WSAGetLastError());
        WSACleanup();
        return 1;
    }
    //---------------------------------------------
    // Clean up and quit.
    wprintf(L"Exiting.\n");
    WSACleanup();
}

float get_random()
{
    return ((float)rand())/RAND_MAX * 100.0;
}

void stress_test_server()
{
    char SendBuf[1024];
    int BufLen = 1024;
    Packet packet = {0};
    float tmp;

    for(int i=0;i<2;i++)
    {
        for(int j=1;j<=10;j++)
        {
            packet.id = (long long)j;
            packet.fill_level = get_random();
            packet.temp = get_random();
            packet.humidity = get_random();
            make_buffer_from_packet(&packet,SendBuf,BufLen);
            send_Buffer(SendBuf,BufLen);
        } 
    }
}

int main()
{
    client_init();

    stress_test_server();

    client_close();
    return 0;
}