#ifndef UNICODE
#define UNICODE
#endif

#define WIN32_LEAN_AND_MEAN
#define UPDATE_TIME 0

#include <winsock2.h>
#include <Ws2tcpip.h>
#include <stdio.h>
#include <pthread.h>
#include "server.h"
#include "bins.h"

// Link with ws2_32.lib
#pragma comment(lib, "Ws2_32.lib")

void *server_update(void *arg);

static SOCKET RecvSocket;
static pthread_t update_thread;

int server_init()
{
    int iResult = 0;

    WSADATA wsaData;

    struct sockaddr_in RecvAddr;

    unsigned short Port = 27015;

    //-----------------------------------------------
    // Initialize Winsock
    iResult = WSAStartup(MAKEWORD(2, 2), &wsaData);
    if (iResult != NO_ERROR) {
        wprintf(L"WSAStartup failed with error %d\n", iResult);
        return 1;
    }

    //-----------------------------------------------
    // Create a receiver socket to receive datagrams
    RecvSocket = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
    if (RecvSocket == INVALID_SOCKET) {
        wprintf(L"socket failed with error %d\n", WSAGetLastError());
        return 1;
    }
    //-----------------------------------------------
    // Bind the socket to any address and the specified port.
    RecvAddr.sin_family = AF_INET;
    RecvAddr.sin_port = htons(Port);
    RecvAddr.sin_addr.s_addr = inet_addr("127.0.0.1"); // htonl(INADDR_ANY);

    iResult = bind(RecvSocket, (SOCKADDR *) & RecvAddr, sizeof (RecvAddr));
    if (iResult != 0) {
        wprintf(L"bind failed with error %d\n", WSAGetLastError());
        return 1;
    }

    printf("Server Initialised.\n");

    if(pthread_create(&update_thread,NULL,&server_update,NULL)!=0){
        printf("Failed to create thread.\n");
        exit(1);
    }

    return 0;
}

void get_Recv_Buffer(char *RecvBuf,int BufLen)
{
    struct sockaddr_in SenderAddr;
    int SenderAddrSize = sizeof (SenderAddr); 
    int iResult = 0;
    
    //-----------------------------------------------
    // Call the recvfrom function to receive datagrams
    // on the bound socket.
    wprintf(L"Receiving datagrams...\n");
    iResult = recvfrom(RecvSocket,
                       RecvBuf, BufLen, 0, (SOCKADDR *) & SenderAddr, &SenderAddrSize);
    if (iResult == SOCKET_ERROR) {
        wprintf(L"recvfrom failed with error %d\n", WSAGetLastError());
    }

}

void *server_update(void *arg)
{
    time_t start_time,current_time;
    time(&start_time);

    Packet packet = {0};

    while(1){
        time(&current_time);
        if((current_time-start_time)<UPDATE_TIME){
            continue;
        }
        get_Packet(&packet);
        pthread_testcancel(); //sets up a cancellation end point
        printf("Packet fetched.\n");
        update_bin(&packet);
        show_bins();
        
        start_time = current_time;
    }
    return NULL;
}

int server_close()
{
    pthread_cancel(update_thread); //requests cancellation at a cancellation endpoint

    int iResult = 0;

    //-----------------------------------------------
    // Close the socket when finished receiving datagrams
    wprintf(L"Finished receiving. Closing socket.\n");
    iResult = closesocket(RecvSocket);
    if (iResult == SOCKET_ERROR) {
        wprintf(L"closesocket failed with error %d\n", WSAGetLastError());
        return 1;
    }

    //-----------------------------------------------
    // Clean up and exit.
    wprintf(L"Exiting.\n");
    WSACleanup();
    return 0;
}