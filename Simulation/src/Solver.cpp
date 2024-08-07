#include "Simulation/Solver.h"

namespace Simulation {
	std::unique_ptr<Solver> Solver::solver = nullptr;
}

Simulation::Solver* Simulation::Solver::getInstance()
{
	if (solver == nullptr) {
		solver = std::unique_ptr<Solver>(new Solver());
	}

	return solver.get();
}

const Simulation::DensityGrid& Simulation::Solver::getDensityMatrix(int w, int h)
{
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
}