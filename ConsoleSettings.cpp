#include "ConsoleSettings.h"
#include <Windows.h>

HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

void ConsoleSettings::HideCursor()
{
	CONSOLE_CURSOR_INFO curInfo;
	GetConsoleCursorInfo(hConsole, &curInfo);
	curInfo.bVisible = FALSE;
	SetConsoleCursorInfo(hConsole, &curInfo);
}

void ConsoleSettings::ShowCursor()
{
	CONSOLE_CURSOR_INFO curInfo;
	GetConsoleCursorInfo(hConsole, &curInfo);
	curInfo.bVisible = TRUE;
	SetConsoleCursorInfo(hConsole, &curInfo);
}

void ConsoleSettings::SetTextColor(const unsigned char& color)
{
	SetConsoleTextAttribute(hConsole, (WORD&)color);
}