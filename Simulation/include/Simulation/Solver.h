#pragma once

#include "Grid.h"
#include "SolverInterface.h"

#define IX(i,j) ((i)+(data.N+2)*(j))
#define SWAP(x0,x) {float * tmp=x0;x0=x;x=tmp;}

#define FOR_EACH_CELL for ( i=1 ; i<=data.N ; i++ ) { for ( j=1 ; j<=data.N ; j++ )
#define END_FOR }

namespace Simulation {
	class Solver : public ISolver
	{
	public:
		virtual bool init(int resolution) override;

		static Solver* getInstance();

		virtual void step() override;

		virtual const GridDto& getDensityMatrix(int w, int h) override;

		Solver(Solver& other) = delete;
		void operator=(const Solver&) = delete;

	protected:
		Solver() = default;

	protected:
		static std::unique_ptr<Solver> solver;

	private:
		void stepVelocity();
		void stepDensity();

		void project();
		void advect(int b, float* d, float* d0, float* u, float* v);
		void diffuse(int b, float* x, float* x0);

		void linearSolve(int b, float* x, float* x0, float a, float c);
		void applyBounds(int b, float* x);
		void addNodeSource(float* x, float* s);

	private:
		GridData data;
		GridDto lastSent;
	};
}

// Macros get undefined in source file