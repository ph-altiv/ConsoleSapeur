#include <iostream>
#include <conio.h>
#include "Field.h"
#include "ConsoleSettings.h"
#include "Cells.h"


void ActivateCell(const int& x, const int& y)
{
	static constexpr unsigned short curCellCol = 0x2B;
	static int lastx = 0, lasty = 0;
	auto par = cells::GetCellParameters(field::Field(lastx, lasty));
	static auto changeColor = [](const int& color, const cells::CellParameters& par)
	{
		cs::CursorPos(lastx, lasty);
		cs::SetTextColor(color);
		std::cout << par.symbol;
	};
	changeColor(par.color, par);
	lastx = x;
	lasty = y;
	par = cells::GetCellParameters(field::Field(lastx, lasty));
	changeColor(curCellCol, par);
}

inline void DrawField()
{
	static const int w = field::Field.Width(),
		h = field::Field.Height();
	cells::CellParameters par;
	for (int i = 0; i < h; i++)
	{
		cs::CursorPos(0, i);
		for (int j = 0; j < w; j++)
		{
			par = cells::GetCellParameters(field::Field(j, i));
			cs::SetTextColor(par.color);
			std::cout << par.symbol;
		}
	}
}

inline void Control(const int& key)
{
	static int x = 0, y = 0;
	static const int
		mx = (field::Field.Width() - 1),
		my = (field::Field.Height() - 1);
	switch (key)
	{
	case 13: // enter
		field::Field.Show(x, y);
		DrawField();
		break;
	case 32: // space
		break;
	case 72: // up
		y -= (y > 0) ? 1 : 0;
		break;
	case 75: // left
		x -= (x > 0) ? 1 : 0;
		break;
	case 77: // right
		x += (x < mx) ? 1 : 0;
		break;
	case 80: // down
		y += (y < my) ? 1 : 0;
		break;
	}
	ActivateCell(x, y);
}

int main() {
	cs::HideCursor();
	int key;
	DrawField();
	ActivateCell(0, 0);
	while ((key = _getch()) != 27)
		Control(key);
	return 0;
}