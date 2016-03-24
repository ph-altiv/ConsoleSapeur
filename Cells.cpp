#define CELLS_CPP
#include "Cells.h"
#include <map>
#include <fstream>
#include <string>
#include <sstream>

std::map<cells::CellTypeName, cells::CellParameters> mTypeParameters;

cells::GetCellParameters::GetCellParameters()
{
	std::ifstream f("CellSettings");
	std::string ln;
	int a, b;
	char c;
	std::stringstream sstr;
	sstr >> std::hex;
	while (!f.eof())
	{
		std::getline(f, ln);
		sstr.str(ln);
		a = -1;
		c = ' ';
		sstr >> a >> b >> c;
		if (a >= 0 && a < CELLTYPENAME_QUANTITY)
			mTypeParameters[(cells::CellTypeName)a] = cells::CellParameters{(unsigned short)b, c};
		sstr.clear();
	}
	f.close();
	if (mTypeParameters.size() != CELLTYPENAME_QUANTITY)
		throw std::exception("Error: invalid file 'CellSettings'");
}

cells::CellParameters cells::GetCellParameters::operator() (cells::CellTypeName type) const
{
	return mTypeParameters[type];
}

cells::CellParameters cells::GetCellParameters::operator() (int type) const
{
	return mTypeParameters[(cells::CellTypeName)type];
}