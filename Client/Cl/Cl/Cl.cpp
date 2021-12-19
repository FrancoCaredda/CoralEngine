#pragma comment(lib, "ws2_32.lib")
#include <winsock2.h>
#include <iostream>

#pragma warning(disable: 4996)

int main(int argc, char* argv[]) {
	//WSAStartup
	WSAData wsaData;
	WORD DLLVersion = MAKEWORD(2, 1);
	if (WSAStartup(DLLVersion, &wsaData) != 0) {
		std::cout << "Error" << std::endl;
		exit(1);
	}

	SOCKADDR_IN addr;
	int sizeofaddr = sizeof(addr);
	addr.sin_addr.s_addr = inet_addr("127.0.0.1");
	addr.sin_port = htons(1111);
	addr.sin_family = AF_INET;

	SOCKET Connection = socket(AF_INET, SOCK_STREAM, NULL);
	while (connect(Connection, (SOCKADDR*)&addr, sizeof(addr)) != 0) {
		std::cout << "Error: failed connect to server.\n";
		SOCKET Connection = socket(AF_INET, SOCK_STREAM, NULL);
	}

	//SOCKET Connection = socket(AF_INET, SOCK_STREAM, NULL);
	/*if (connect(Connection, (SOCKADDR*)&addr, sizeof(addr)) != 0) {
		std::cout << "Error: failed connect to server.\n";
		continue;
	}*/
	std::cout << "Connected!\n";
	
	
	while (true) {
		/*if (connect(Connection, (SOCKADDR*)&addr, sizeof(addr)) != 0) {
			std::cout << "Error: failed connect to server.\n";
			return 0;
		}*/

		int msg_size;
		recv(Connection, (char*)&msg_size, sizeof(int), NULL);

		char* msg = new char[msg_size + 1];
		msg[msg_size] = '\0';

		recv(Connection, msg, msg_size, NULL);

		std::string s = msg;
		std::cout << s << std::endl;
		delete[] msg;
	}
	
	system("pause");
	return 0;
}