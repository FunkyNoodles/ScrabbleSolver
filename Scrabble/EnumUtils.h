#pragma once
#include "Placement.h"
namespace EnumUtils
{
	inline PlacementType getOther(const PlacementType type) {
		return (type == PlacementType::DOWN) ? PlacementType::CROSS : PlacementType::DOWN;
	}

	inline void setIncrements(const PlacementType type, int & rinc, int & cinc) {
		if (type == PlacementType::CROSS) {
			rinc = 0;
			cinc = 1;
		}
		else {
			rinc = 1;
			cinc = 0;
		}
	}

	inline void setDecrements(const PlacementType type, int & rdec, int & cdec) {
		if (type == PlacementType::CROSS) {
			rdec = 0;
			cdec = -1;
		}
		else {
			rdec = -1;
			cdec = 0;
		}
	}
};
