#pragma once

#include "Grid.h"

namespace Simulation {
	class ISolver {
	public:
		virtual const DensityGrid& getDensityMatrix(int w, int h) = 0;
	};
}