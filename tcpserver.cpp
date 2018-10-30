#define _WINSOCK_DEPRECATED_NO_WARNINGS
#include <iostream>
#include<winsock2.h>
#include <fcntl.h>
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
	int nFlag = 1;
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

	printf("Input local port:");
	std::cin >> localport;
	getchar();

	setsockopt(sd, SOL_SOCKET, SO_REUSEADDR, (char *)&nFlag, sizeof(nFlag));
	//先调用connect()函数，为套接字指定目的地址/端口
	svr_addr.sin_family = AF_INET;
	svr_addr.sin_port = htons(localport);
	svr_addr.sin_addr.s_addr = inet_addr("192.168.0.106"); 
	err = bind(sd, (struct sockaddr*)&svr_addr, addrlen);
	if (err < 0)
	{
		return S_FALSE;
	}

	err = listen(sd, 2);
	if (err < 0)
	{
		return S_FALSE;
	}
	printf("Waiting for Connecting.\r\n");

	SOCKET fd;
	int cli_len = sizeof(sockaddr_in);
	struct sockaddr_in client_addr;
	while (1)
	{
		
		err = accept(sd, (sockaddr*)&client_addr, &cli_len);
		if (err < 0)
		{
			continue;
		}
		fd = err;

		err = recv(fd, buf, BUFSZ, 0);
		if (err < 0)
		{
			return S_FALSE;
		}
		err = send(fd, buf, BUFSZ, 0);
		if (err < 0)
		{
			return S_FALSE;
		}
		printf("client: IPAddr = %s, Port = %d, buf = %s\n", inet_ntoa(client_addr.sin_addr), ntohs(client_addr.sin_port), buf);

		closesocket(fd);
	}

	closesocket(sd);
	return 0;
}