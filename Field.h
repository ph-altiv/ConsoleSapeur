#pragma once
#include "Cells.h"

namespace field
{
	class Field
	{
	public:
		Field();
		cells::CellTypeName operator() (int x, int y) const;
		cells::CellTypeName Show(int x, int y) const;
		int Height() const;
		int Width() const;
	}
#ifndef FIELD_CPP
	static const Field
#endif
	;
}