#pragma once
#include "Cells.h"

namespace field
{
	class Field
	{
	public:
		Field();
		cells::CellTypeName operator() (const int& x, const int& y) const;
		bool Show(const int& x, const int& y) const;
		void Mark(const int& x, const int& y) const;
		int Height() const;
		int Width() const;
	}
#ifndef FIELD_CPP
	static const Field
#endif
	;
}