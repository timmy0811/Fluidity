#pragma once

#include "Grid.h"

namespace Simulation {
	class ISolver {
	public:
		virtual const GridDto& getDensityMatrix(int w, int h) = 0;
		virtual void step() = 0;
		virtual bool init(int resolution) = 0;
	};
}