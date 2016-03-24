#include "ConsoleSettings.h"
#include <Windows.h>

HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

void cs::HideCursor()
{
	CONSOLE_CURSOR_INFO curInfo;
	GetConsoleCursorInfo(hConsole, &curInfo);
	curInfo.bVisible = FALSE;
	SetConsoleCursorInfo(hConsole, &curInfo);
}

void cs::ShowCursor()
{
	CONSOLE_CURSOR_INFO curInfo;
	GetConsoleCursorInfo(hConsole, &curInfo);
	curInfo.bVisible = TRUE;
	SetConsoleCursorInfo(hConsole, &curInfo);
}

void cs::SetTextColor(const unsigned char& color)
{
	SetConsoleTextAttribute(hConsole, (WORD&)color);
}

void cs::CursorPos(const int& x, const int& y)
{
	SetConsoleCursorPosition(hConsole, COORD{ (SHORT)x, (SHORT)y });
}