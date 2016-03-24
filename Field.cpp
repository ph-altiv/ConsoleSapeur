#define FIELD_CPP
#include "Field.h"
#include <vector>
#include <fstream>
#include <string>
#include <sstream>
#include <map>
#include <ctime>

int height, width, mines, vecsize;
#define CoordToIndex(x, y) (x + y*width)

std::vector<cells::CellTypeName> fieldcells;
std::vector<cells::CellTypeName> gamefield;

inline void upcell(const int& ind)
{
	if (ind >= 0 && ind < vecsize && fieldcells[ind] != cells::MINED_CELL)
		fieldcells[ind] = (cells::CellTypeName)(fieldcells[ind] + 1);
}

inline void fillField()
{
	srand((unsigned char)time(0));
	int subind, empty = vecsize;
	for (int i = 0; i < mines; i++)
	{
		subind = rand() % empty--;
		int j = 0;
		while (j < vecsize && subind > 0)
		{
			if (fieldcells[j] != cells::MINED_CELL)
				subind--;
			j++;
		}
		fieldcells[j] = cells::MINED_CELL;
		upcell(j - width);
		upcell(j + width);
		if (j % width > 0)
		{
			upcell(j - 1);
			upcell(j - 1 - width);
			upcell(j - 1 + width);
		}
		if ((j + 1) % width > 0)
		{
			upcell(j + 1);
			upcell(j + 1 - width);
			upcell(j + 1 + width);
		}
	}
}

field::Field::Field()
{
	static const std::map<std::string, int> parNames{
		{"Size:",	1},
		{"Mines:",	2}
	};
	std::ifstream f("FieldSettings");
	std::string ln, par;
	std::stringstream sstr;
	std::string;
	while (!f.eof())
	{
		std::getline(f, ln);
		sstr.str(ln);
		sstr >> par;
		switch (parNames.at(par))
		{
		case 1: // Size:
			sstr >> height >> width;
			break;
		case 2: // Mines:
			sstr >> mines;
			break;
		}
		sstr.clear();
	}
	if (height <= 0 || width <= 0 || mines < 0 || height > 50 || width > 50 || mines > (vecsize = height * width))
		throw std::exception("Error: invalid file 'FieldSettings'");
	fieldcells.resize(vecsize, cells::ZERO_CELL);
	gamefield.resize(vecsize, cells::HIDDEN_CELL);
	fillField();
}

cells::CellTypeName field::Field::operator() (int x, int y) const
{
	return gamefield[CoordToIndex(x, y)];
}

cells::CellTypeName field::Field::Show(int x, int y) const
{
	int ind = CoordToIndex(x, y);
	return (gamefield[ind] = fieldcells[ind]);
}