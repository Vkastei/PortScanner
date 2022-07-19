#define _WINSOCK_DEPRECATED_NO_WARNINGS


#include <winsock2.h>
#include <iostream>
#include <vector>

#pragma comment(lib, "Ws2_32.lib")

sockaddr_in addr;


void checkPort(SOCKET s, int port, char* ip, std::vector<int> openPorts) {

	

	addr.sin_addr.S_un.S_addr = inet_addr(ip);
	addr.sin_port = htons(port);
	addr.sin_family = AF_INET;

	try
	{
		

		
		connect(s, (const sockaddr*)&addr, sizeof(addr));
		std::cout << "connecting " << port << ip << std::endl;
		openPorts.push_back(port);
	}
	catch (...)
	{
		
	}

	

}

void setup(char* ip) {

	
	SOCKET s;
	
	WSAData wsaData;
	std::vector<int> openPorts;
	
	try
	{
		WSAStartup(MAKEWORD(2, 2), &wsaData);

		s = socket(AF_INET, IPPROTO_TCP, 0);
		
		for (int i = 0; i < 65535; i++) {

			
			
			
			checkPort(s, i, ip, openPorts);

		
		}
	}
	catch (...)
	{
		std::cout << "Something doesnt work : " << WSAGetLastError() << std::endl;
	}


	for (int i : openPorts) {
		std::cout << i << std::endl;
	}
	
	
}

int main() {

	char ip[1024];
	std::cout << "IP to check:" << std::endl;
	std::cin >> ip;
	setup(ip);
}