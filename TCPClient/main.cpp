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

// В опциях проекта, в разделе Linker, в пункте Additional Dependancies укажите Ws2_32.lib
#pragma comment(lib, "Ws2_32.lib")

int  main(void)
{
	WSADATA wsaData;
	SOCKET ConnectSocket;  // впускающий сокет и сокет для клиентов
	sockaddr_in ServerAddr;  // это будет адрес сервера
	int err, maxlen = 1024;  // код ошибки и размер буферов
	char recvbuf [10];  // буфер приема
	char query [512];  // буфер отправки
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
	// отправляем запрос на сервер
	//send(ConnectSocket, query, strlen(query), 0);
	//printf("Sent: %s\n", query);

	// получаем результат
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