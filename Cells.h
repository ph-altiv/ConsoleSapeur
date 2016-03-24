#pragma once

namespace cells
{
	constexpr int CELLTYPENAME_QUANTITY = 12;

	enum CellTypeName
	{
		ZERO_CELL = 0,
		ONE_CELL = 1,
		TWO_CELL = 2,
		THREE_CELL = 3,
		FOUR_CELL = 4,
		FIVE_CELL = 5,
		SIX_CELL = 6,
		SEVEN_CELL = 7,
		EIGHT_CELL = 8,
		HIDDEN_CELL = 9,
		MARKED_CELL = 10,
		MINED_CELL = 11
	};

	struct CellParameters
	{
		unsigned short color;
		char symbol;
	};
	
	class GetCellParameters
	{
	public:
		GetCellParameters();
		CellParameters operator() (const CellTypeName type) const;
		CellParameters operator() (const int type) const;
	}
#ifndef CELLS_CPP
	static const GetCellParameters
#endif
	;
}