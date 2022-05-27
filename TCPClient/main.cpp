#define _WINSOCK_DEPRECATED_NO_WARNINGS

#include <winsock2.h>
#include <ws2tcpip.h>
#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <string>

#define DEFAULT_BUFLEN 10

int recvbuflen = DEFAULT_BUFLEN;


 
using namespace std;

// � ������ �������, � ������� Linker, � ������ Additional Dependancies ������� Ws2_32.lib
#pragma comment(lib, "Ws2_32.lib")

int  main(void)
{
	WSADATA wsaData;
	SOCKET ConnectSocket;  // ���������� ����� � ����� ��� ��������
	sockaddr_in ServerAddr;  // ��� ����� ����� �������
	int err, maxlen = 1024;  // ��� ������ � ������ �������
	char recvbuf [10];  // ����� ������
	char query [512];  // ����� ��������
	string server;
	std::string myString;
	int port;

	std::cout << "Please Enter address Server" << std::endl;
	getline(cin, server);
	std::cout << "Please Enter Port" << std::endl;
	cin >> port;

	// Initialize Winsock
	WSAStartup(MAKEWORD(2, 2), &wsaData);

	// Connect to server
	ConnectSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

	ServerAddr.sin_family = AF_INET;
	//ServerAddr.sin_addr.s_addr = inet_addr("127.0.0.1");
	ServerAddr.sin_addr.s_addr = inet_addr(server.c_str());
	//ServerAddr.sin_port = htons(12345);
	ServerAddr.sin_port = htons(port);

	err = connect(ConnectSocket, (sockaddr*)&ServerAddr, sizeof(ServerAddr));

	if (err == SOCKET_ERROR) {
		printf("connect failed: %d\n", WSAGetLastError());
		closesocket(ConnectSocket);
		WSACleanup();
		return 1;
	}
	else
		cout << "Server OK" << endl;

//	_snprintf_s(query, maxlen, maxlen, "CALC * 12 6\n");
	// ���������� ������ �� ������
	//send(ConnectSocket, query, strlen(query), 0);
	//printf("Sent: %s\n", query);

	// �������� ���������
//	while (true) {

	int iResult;

	do {
		iResult = recv(ConnectSocket, recvbuf, recvbuflen, 0);
		if (iResult > 0) {
			printf("Bytes received: %d\n", iResult);
			std::cout << recvbuf <<std::endl;
			memset(recvbuf, 0, sizeof(recvbuf));
		}
		else if (iResult == 0)
			printf("Connection closed\n");
		else
			printf("recv failed: %d\n", WSAGetLastError());
	} while (iResult > 0);


		//}
		/*while ((nDataLength = recv(ConnectSocket, recvbuf, sizeof(recvbuf), 0)) > 0) {
			myString.append(recvbuf, nDataLength);
			
		}
		std::cout << myString << "\n";*/

		
		
	//}

	// shutdown the connection since we're done
	closesocket(ConnectSocket);

}