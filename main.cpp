#include <iostream>
#include "ConsoleSettings.h"
#include "Cells.h"

int main() {
	std::cout << std::hex;
	for (int i = 0; i < cells::CELLTYPENAME_QUANTITY; i++)
	{
		cells::CellParameters cp = cells::GetCellParameters(i);
		std::cout << (int)cp.color << '\t' << cp.symbol << std::endl;
	}
	return 0;
}