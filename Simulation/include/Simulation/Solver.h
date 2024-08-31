#pragma once

#include "Grid.h"
#include "SolverInterface.h"

#define IX(i,j) ((std::min(i, data.N - 1) < 0 ? 0 : std::min(i, data.N - 1)) + (data.N) * (std::min(j, data.N - 1) < 0 ? 0 : std::min(j, data.N - 1)))

#define SWAP(x0,x) {float * tmp=x0;x0=x;x=tmp;}

#define FOR_EACH_CELL for ( int j=1 ; j<=data.N - 1 ; j++ ) { for ( int i=1 ; i<=data.N - 1 ; i++ )
#define END_FOR }

namespace Simulation {
	class Solver : public ISolver
	{
	public:
		virtual bool init(int resolution) override;

		static Solver* getInstance();

		virtual inline void step() override;

		virtual GridDto getDensityMatrix(int w, int h) override;

		virtual void addNodeDens(int x, int y, float dens) override;
		virtual void addNodeVel(int x, int y, float velX, float velY) override;

		inline void setDt(float dt) { data.dt = dt; }

		Solver(Solver& other) = delete;
		void operator=(const Solver&) = delete;

	protected:
		Solver() = default;

	protected:
		static std::unique_ptr<Solver> solver;

	private:
		void stepSimulation();

		void project(float* velX, float* velY, float* p, float* div);
		void advect(int b, float* d, float* d0, float* u, float* v);
		void diffuse(int b, float* x, float* x0);

		void linearSolve(int b, float* x, float* x0, float a, float c, int iter);
		void applyBounds(int b, float* x);

	private:
		GridData data;
		GridDto lastSent;
	};
}

// Macros get undefined in source file