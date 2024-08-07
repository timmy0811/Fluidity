#pragma once

#include "Grid.h"
#include "SolverInterface.h"

namespace Simulation {
	class Solver : public ISolver
	{
	public:
		static Solver* getInstance();

		virtual const DensityGrid& getDensityMatrix(int w, int h) override;

		Solver(Solver& other) = delete;
		void operator=(const Solver&) = delete;

	protected:
		Solver() = default;

	protected:
		static std::unique_ptr<Solver> solver;

	private:
		inline static DensityGrid grid;
	};
}
