#pragma once

#include <memory>

namespace Simulation {
	struct DensityGrid {
		bool hasChanged = false;
		bool hasChangedDim = false;
		unsigned w, h;
		int* mat;

		~DensityGrid() {
			free(mat);
		}
	};
}