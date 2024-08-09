#include "Simulation/Solver.h"

namespace Simulation {
	std::unique_ptr<Solver> Solver::solver = nullptr;
}

bool Simulation::Solver::init(int resolution)
{
	data.allocate();
	data.clear();

	data.N = resolution - 2;

	return false;
}

Simulation::Solver* Simulation::Solver::getInstance()
{
	if (solver == nullptr) {
		solver = std::unique_ptr<Solver>(new Solver());
	}

	return solver.get();
}

void Simulation::Solver::step()
{
	stepVelocity();
	stepDensity();
}

const Simulation::GridDto& Simulation::Solver::getDensityMatrix(int w, int h)
{
	GridDto dto{};
	dto.hasChanged = true;
	dto.hasChangedDim = false;
	dto.mat = data.dens;

	//if (lastSent.w != w || lastSent.h != h || !lastSent.mat) {
	//	data.resize(w); // Only Quad now

	//	dto.w = w;
	//	dto.h = h;

	//	dto.hasChangedDim = true;
	//}

	//static bool tempVar = true;

	//if (tempVar || dto.hasChangedDim) {
	//	for (int i = 0; i < w * h; i++) {
	//		dto.mat[i] = rand() % 100;
	//	}

	//	dto.hasChanged = true;
	//	tempVar = false;
	//}
	//dto.hasChanged = false;
	//dto.mat = data.dens;

	lastSent = dto;

	return dto;
}

void Simulation::Solver::stepVelocity()
{
	addNodeSource(data.u, data.u_prev);
	addNodeSource(data.v, data.v_prev);

	SWAP(data.u, data.u_prev);
	diffuse(1, data.u, data.u_prev);
	SWAP(data.v, data.v_prev);
	diffuse(2, data.v, data.v_prev);

	project();

	SWAP(data.u, data.u_prev);
	SWAP(data.v, data.v_prev);

	advect(1, data.u, data.u_prev, data.u_prev, data.v_prev);
	advect(2, data.v, data.v_prev, data.u_prev, data.v_prev);
	project();
}

void Simulation::Solver::stepDensity()
{
	addNodeSource(data.dens, data.dens_prev);

	SWAP(data.dens, data.dens_prev);
	diffuse(0, data.dens, data.dens_prev);

	SWAP(data.dens, data.dens_prev);
	advect(0, data.dens, data.dens_prev, data.u, data.v);
}

void Simulation::Solver::project()
{
	// project ( N, u, v, u0, v0 );
	int i, j;

	FOR_EACH_CELL{
		data.v_prev[IX(i, j)] = -0.5f * (data.u[IX(i + 1, j)] - data.u[IX(i - 1, j)] + data.v[IX(i, j + 1)] - data.v[IX(i, j - 1)]) / data.N;
		data.u_prev[IX(i, j)] = 0;
	}END_FOR

		applyBounds(0, data.v_prev);
	applyBounds(0, data.u_prev);
	linearSolve(0, data.u_prev, data.v_prev, 1, 4);

	FOR_EACH_CELL{
		data.u[IX(i, j)] -= 0.5f * data.N * (data.u_prev[IX(i + 1, j)] - data.u_prev[IX(i - 1, j)]);
		data.v[IX(i, j)] -= 0.5f * data.N * (data.u_prev[IX(i, j + 1)] - data.u_prev[IX(i, j - 1)]);
	}END_FOR

		applyBounds(1, data.u);
	applyBounds(2, data.v);
}

void Simulation::Solver::advect(int b, float* d, float* d0, float* u, float* v)
{
	int i, j, i0, j0, i1, j1;
	float x, y, s0, t0, t1, s1, dt0;

	dt0 = data.N * data.dt;
	FOR_EACH_CELL{
		x = i - dt0 * u[IX(i, j)];
		y = j - dt0 * v[IX(i, j)];

		std::max(x, 0.5f);
		std::min(x, data.N + 0.5f);
		i0 = (int)x;
		i1 = i0 + 1;

		std::max(y, 0.5f);
		std::min(y, data.N + 0.5f);
		j0 = (int)y;
		j1 = j0 + 1;

		s1 = x - i0;
		s0 = 1 - s1;

		t1 = y - j0;
		t0 = 1 - t1;

		d[IX(i, j)] = s0 * (t0 * d0[IX(i0, j0)] + t1 * d0[IX(i0, j1)]) +
			s1 * (t0 * d0[IX(i1, j0)] + t1 * d0[IX(i1, j1)]);
	}END_FOR

		applyBounds(b, d);
}

void Simulation::Solver::diffuse(int b, float* x, float* x0)
{
	float a = data.dt * data.diff * std::pow(data.N, 2.0);
	linearSolve(b, x, x0, a, 1 + 4 * a);
}

void Simulation::Solver::linearSolve(int b, float* x, float* x0, float a, float c)
{
	int i, j, k;

	for (k = 0; k < 20; k++) {
		FOR_EACH_CELL{
			x[IX(i, j)] = (x0[IX(i, j)] + a * (x[IX(i - 1, j)] + x[IX(i + 1, j)] + x[IX(i, j - 1)] + x[IX(i, j + 1)])) / c;
		}END_FOR

			applyBounds(b, x);
	}
}

void Simulation::Solver::applyBounds(int b, float* x)
{
	for (int i = 0; i <= data.N; i++) {
		x[IX(0, i)] = b == 1 ? -x[IX(1, i)] : x[IX(1, i)];
		x[IX(data.N + 1, i)] = b == 1 ? -x[IX(data.N, i)] : x[IX(data.N, i)];
		x[IX(i, 0)] = b == 2 ? -x[IX(i, 1)] : x[IX(i, 1)];
		x[IX(i, data.N + 1)] = b == 2 ? -x[IX(i, data.N)] : x[IX(i, data.N)];
	}

	x[IX(0, 0)] = 0.5f * (x[IX(1, 0)] + x[IX(0, 1)]);
	x[IX(0, data.N + 1)] = 0.5f * (x[IX(1, data.N + 1)] + x[IX(0, data.N)]);
	x[IX(data.N + 1, 0)] = 0.5f * (x[IX(data.N, 0)] + x[IX(data.N + 1, 1)]);
	x[IX(data.N + 1, data.N + 1)] = 0.5f * (x[IX(data.N, data.N + 1)] + x[IX(data.N + 1, data.N)]);
}

void Simulation::Solver::addNodeSource(float* x, float* s)
{
	for (int i = 0; i < data.size; i++) {
		x[i] += data.dt * s[i];
	}
}

#undef IX
#undef SWAP
#undef FOR_EACH_CELL
#undef END_FOR