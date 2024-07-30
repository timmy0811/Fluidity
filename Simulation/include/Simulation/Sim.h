#pragma once

namespace Sim {
	typedef struct {
		unsigned w, h;
		short* mat;
	} DensityGrid;

	DensityGrid* getDensityMatrix() { return nullptr; };
}