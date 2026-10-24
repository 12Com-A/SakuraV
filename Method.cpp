#include "ClientNeed.h"

std::string GetConsoleContent() {
	HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
	if (handle == INVALID_HANDLE_VALUE) return "INVALID_HANDLE_VALUE";
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	if (!GetConsoleScreenBufferInfo(handle, &csbi)) return "GetConsoleScreenBufferInfoError";
	COORD cursorPos = csbi.dwCursorPosition;
	DWORD totalChars = (csbi.dwSize.X * cursorPos.Y) + cursorPos.X;

	if (totalChars == 0) return "";

	std::vector<char> buffer(totalChars + 1, 0);
	COORD startCoord = { 0, 0 };
	DWORD charsRead = 0;

	if (ReadConsoleOutputCharacterA(handle, buffer.data(), totalChars, startCoord, &charsRead)) {
		buffer[charsRead] = '\0';
		return std::string(buffer.data(), charsRead);
	}
	return "";
}