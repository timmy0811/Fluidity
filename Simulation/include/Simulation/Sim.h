#pragma once

namespace Sim {
	struct DensityGrid {
		bool hasChanged = false;
		bool hasChangedDim = false;
		unsigned w, h;
		int* mat;

		~DensityGrid() {
			free(mat);
		}
	};

	static DensityGrid grid;

	const DensityGrid& getDensityMatrix(int w, int h) {
		grid.hasChangedDim = false;
		if (grid.w != w || grid.h != h || !grid.mat) {
			free(grid.mat);
			grid.mat = (int*)malloc(static_cast<unsigned long long>(w) * h * sizeof(int));

			grid.w = w;
			grid.h = h;

			grid.hasChangedDim = true;
		}

		static bool tempVar = true;

		if (tempVar || grid.hasChangedDim) {
			for (int i = 0; i < w * h; i++) {
				grid.mat[i] = rand() % 100;
			}

			grid.hasChanged = true;
			tempVar = false;
		}
		grid.hasChanged = false;

		return grid;
	};
}