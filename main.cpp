#include <iostream>
#include "Field.h"
#include "ConsoleSettings.h"
#include "Cells.h"

void DrawField()
{
	static const int w = field::Field.Width(),
		h = field::Field.Height();
	cells::CellTypeName type;
	cells::CellParameters par;
	for (int i = 0; i < h; i++)
	{
		cs::CursorPos(0, i);
		for (int j = 0; j < w; j++)
		{
			type = field::Field(j, i);
			par = cells::GetCellParameters(type);
			cs::SetTextColor(par.color);
			std::cout << par.symbol;
		}
	}
}

int main() {
	DrawField();
	return 0;
}