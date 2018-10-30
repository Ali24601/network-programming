#define _WINSOCK_DEPRECATED_NO_WARNINGS
#include <iostream>
#include<winsock2.h>
#pragma comment(lib,"ws2_32.lib")
#define BUFSZ 512
int main(int argc, char *argv[])
{
	SOCKET sd;
	int localport;
	struct sockaddr_in svr_addr;
	int addrlen = sizeof(struct sockaddr_in);
	char buf[BUFSZ] = {};
	WORD wVersionRequested;
	WSADATA wsaData;
	int err;
	wVersionRequested = MAKEWORD(1, 1);
	err = WSAStartup(wVersionRequested, &wsaData);
	if (err != 0)
	{
		perror("\n\n-----TCP WSAStartup failed------\n\n");
		return S_FALSE;
	}

	if ((sd = socket(AF_INET, SOCK_STREAM, 0)) < 0)
	{
		perror("socket");
		exit(EXIT_FAILURE);
	}

	printf("Input server port:");
	std::cin >> localport;
	getchar();
	//先调用connect()函数，为套接字指定目的地址/端口
	svr_addr.sin_family = AF_INET;
	svr_addr.sin_port = htons(localport);
	svr_addr.sin_addr.s_addr = inet_addr("192.168.0.106"); 
	printf("Waiting for Connecting.\r\n");
	getchar();
	err = connect(sd, (struct sockaddr*)&svr_addr, addrlen); 
	if (err < 0)
	{
		return S_FALSE;
	}

	printf("Connected.\r\n");

	char *msg = "Hello World!";
	send(sd, msg,strlen(msg),0);
	char msgrecv[100] = { 0 };
	recv(sd, msgrecv, 100, 0);
	printf("Received msg:%s .\r\n",msgrecv);
	getchar(); 
	closesocket(sd);
	return 0;
}