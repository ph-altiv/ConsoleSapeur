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

bool Control()
{
	static int x = 0, y = 0;
	static const int
		mx = (field::Field.Width() - 1),
		my = (field::Field.Height() - 1);
	switch (int key = _getch())
	{
	case 13: // enter
	{
		bool b = field::Field.Show(x, y);
		DrawField();
		if (!b)
		{
			while (_getch() != 27);
			return false;
		}
	}
		break;
	case 27: // esc
		return false;
		break;
	case 32: // space
		field::Field.Mark(x, y);
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
	return true;
}

int main() {
	cs::HideCursor();
	DrawField();
	ActivateCell(0, 0);
	while (Control());
	return 0;
}