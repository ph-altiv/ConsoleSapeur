#include "ConsoleSettings.h"
#include <fstream>
#include <Windows.h>

HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

struct StartCursorPosition
{
	int x0, y0;
	StartCursorPosition();
} static const StartCursorPosition;

StartCursorPosition::StartCursorPosition()
{
	std::ifstream f("Position");
	f >> x0 >> y0;
	f.close();
}

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

void cs::SetTextColor(const unsigned short& color)
{
	SetConsoleTextAttribute(hConsole, (WORD&)color);
}

void cs::CursorPos(const int& x, const int& y)
{
	SetConsoleCursorPosition(hConsole, COORD{ (SHORT)(x + StartCursorPosition.x0), (SHORT)(y + StartCursorPosition.y0) });
}