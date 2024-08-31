#pragma once

#include "Grid.h"

namespace Simulation {
	class ISolver {
	public:
		virtual GridDto getDensityMatrix(int w, int h) = 0;
		virtual inline void step() = 0;
		virtual bool init(int resolution) = 0;

		virtual void addNodeDens(int x, int y, float dens) = 0;
		virtual void addNodeVel(int x, int y, float velX, float velY) = 0;
	};
}