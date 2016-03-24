#define FIELD_CPP
#include "Field.h"
#include <vector>
#include <fstream>
#include <string>
#include <sstream>
#include <map>
#include <ctime>

int height, width, mines, vecsize, hidden;
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
	if (height <= 0 || width <= 0 || mines < 0 || height > 25 || width > 100 || mines > (vecsize = height * width))
		throw std::exception("Error: invalid file 'FieldSettings'");
	fieldcells.resize(vecsize, cells::ZERO_CELL);
	gamefield.resize(vecsize, cells::HIDDEN_CELL);
	hidden = vecsize;
	fillField();
}

cells::CellTypeName field::Field::operator() (const int& x, const int& y) const
{
	return gamefield[CoordToIndex(x, y)];
}

void ZeroShow(const int& x, const int& y)
{
	if (x < 0 || y < 0 || x >= width || y >= height)
		return;
	int ind = CoordToIndex(x, y);
	if (gamefield[ind] != cells::HIDDEN_CELL) return;
	gamefield[ind] = fieldcells[ind];
	hidden--;
	if (fieldcells[ind] != cells::ZERO_CELL) return;
	ZeroShow(x - 1, y - 1);
	ZeroShow(x - 1, y);
	ZeroShow(x - 1, y + 1);
	ZeroShow(x, y - 1);
	ZeroShow(x, y + 1);
	ZeroShow(x + 1, y - 1);
	ZeroShow(x + 1, y);
	ZeroShow(x + 1, y + 1);
}

inline void MinesShow()
{
	for (int i = 0; i < vecsize; i++)
		if (fieldcells[i] == cells::MINED_CELL)
			gamefield[i] = cells::MINED_CELL;
}

bool field::Field::Show(const int& x, const int& y) const
{
	if (x < 0 || y < 0 || x >= width || y >= height)
		return true;
	int ind = CoordToIndex(x, y);
	if (gamefield[ind] != cells::HIDDEN_CELL)
		return true;
	switch ((int)fieldcells[ind])
	{
	case (int)cells::ZERO_CELL:
		ZeroShow(x, y);
		break;
	case (int)cells::MINED_CELL:
		MinesShow();
		return false;
		break;
	default:
		gamefield[ind] = fieldcells[ind];
		hidden--;
	}
	return (mines == hidden) ? false : true;
}

int field::Field::Height() const
{
	return height;
}

int field::Field::Width() const
{
	return width;
}