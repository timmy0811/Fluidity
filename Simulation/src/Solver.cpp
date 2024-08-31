#include "Simulation/Solver.h"

#include "Simulation/Log.h"

namespace Simulation {
	std::unique_ptr<Solver> Solver::solver = nullptr;
}

bool Simulation::Solver::init(int resolution)
{
	data.N = resolution;

	data.allocate();
	data.clear();

	data.dt = 0.01;
	data.diff = 0.0;
	data.visc = 0.000001;

	return true;
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
	stepSimulation();
}

Simulation::GridDto Simulation::Solver::getDensityMatrix(int w, int h)
{
	// data.dens[1] += 0.005f;
	GridDto dto{};
	dto.hasChanged = true;
	dto.hasChangedDim = false;
	dto.mat = data.dens;
	dto.h = w;
	dto.w = w;

	lastSent = dto;

	return dto;
}

void Simulation::Solver::addNodeDens(int x, int y, float dens)
{
	//LOG_SIM_TRACE("Adding density to node ({0}, {1}) with value {2}", x, data.N - y - 1, dens);
	data.dens[IX(x, data.N - y - 1)] += dens;
}

void Simulation::Solver::addNodeVel(int x, int y, float velX, float velY)
{
	//LOG_SIM_TRACE("Adding velocity to node ({0}, {1}) with value {2}, {3}", x, data.N - y - 1, velX, velY);
	data.u[IX(x, data.N - y - 1)] += velX;
	data.v[IX(x, data.N - y - 1)] += velY;
}

void Simulation::Solver::stepSimulation()
{
	diffuse(1, data.u_prev, data.u);
	diffuse(2, data.v_prev, data.v);

	project(data.u_prev, data.v_prev, data.u, data.v);

	advect(1, data.u, data.u_prev, data.u_prev, data.v_prev);
	advect(2, data.v, data.v_prev, data.u_prev, data.v_prev);

	project(data.u, data.v, data.u_prev, data.v_prev);

	diffuse(0, data.dens_prev, data.dens);
	advect(0, data.dens, data.dens_prev, data.u, data.v);
}

void Simulation::Solver::project(float* velX, float* velY, float* p, float* div)
{
	const float nRecip = 1.0 / data.N;

	FOR_EACH_CELL{
		div[IX(i, j)] = (-0.5f *
				(velX[IX(i + 1, j)] -
					velX[IX(i - 1, j)] +
					velY[IX(i, j + 1)] -
					velY[IX(i, j - 1)])) * nRecip;

		p[IX(i, j)] = 0;
	}END_FOR

		applyBounds(0, div);
	applyBounds(0, p);
	linearSolve(0, p, div, 1, 6, 4);

	FOR_EACH_CELL{
		velX[IX(i, j)] -= 0.5f * (p[IX(i + 1, j)] - p[IX(i - 1, j)]) * data.N;
		velY[IX(i, j)] -= 0.5f * (p[IX(i, j + 1)] - p[IX(i, j - 1)]) * data.N;
	}END_FOR

		applyBounds(1, velX);
	applyBounds(2, velY);
}

void Simulation::Solver::advect(int b, float* d, float* d0, float* u, float* v)
{
	float i0, i1, j0, j1;

	float dtx = data.dt * (data.N - 2);
	float dty = data.dt * (data.N - 2);

	float s0, s1, t0, t1;
	float tmp1, tmp2, x, y;

	float Nfloat = data.N;
	float ifloat, jfloat;
	int i, j;

	for (j = 1, jfloat = 1; j < data.N - 1; j++, jfloat++) {
		for (i = 1, ifloat = 1; i < data.N - 1; i++, ifloat++) {
			tmp1 = dtx * u[IX(i, j)];
			tmp2 = dty * v[IX(i, j)];
			x = ifloat - tmp1;
			y = jfloat - tmp2;

			x = std::max(x, 0.5f);
			x = std::min(x, Nfloat + 0.5f);
			i0 = std::floor(x);
			i1 = i0 + 1.0f;

			y = std::max(y, 0.5f);
			y = std::min(y, Nfloat + 0.5f);
			j0 = std::floor(y);
			j1 = j0 + 1.0f;

			s1 = x - i0;
			s0 = 1.0f - s1;

			t1 = y - j0;
			t0 = 1.0f - t1;

			int i0i = (int)i0;
			int i1i = (int)i1;
			int j0i = (int)j0;
			int j1i = (int)j1;

			d[IX(i, j)] =
				s0 * (t0 * d0[IX(i0i, j0i)] + t1 * d0[IX(i0i, j1i)]) +
				s1 * (t0 * d0[IX(i1i, j0i)] + t1 * d0[IX(i1i, j1i)]);
		}
	}

	applyBounds(b, d);
}

void Simulation::Solver::diffuse(int b, float* x, float* x0)
{
	float a = data.dt * data.diff * std::pow(data.N - 2, 2);
	linearSolve(b, x, x0, a, 1 + 6 * a, 4);
}

void Simulation::Solver::linearSolve(int b, float* x, float* x0, float a, float c, int iter)
{
	float cRecip = 1.0 / c;

	for (int k = 0; k < iter; k++) {
		FOR_EACH_CELL{
			x[IX(i, j)] = (x0[IX(i, j)] + a * (x[IX(i + 1, j)] + x[IX(i - 1, j)] + x[IX(i, j + 1)] + x[IX(i, j - 1)])) * cRecip;
		}END_FOR

			applyBounds(b, x);
	}
}

void Simulation::Solver::applyBounds(int b, float* x)
{
	for (int i = 1; i <= data.N - 1; i++) {
		x[IX(i, 0)] = b == 2 ? -x[IX(i, 1)] : x[IX(i, 1)];
		x[IX(i, data.N - 1)] = b == 2 ? -x[IX(i, data.N - 2)] : x[IX(i, data.N - 2)];
	}

	for (int j = 1; j <= data.N - 1; j++) {
		x[IX(0, j)] = b == 1 ? -x[IX(1, j)] : x[IX(1, j)];
		x[IX(data.N - 1, j)] = b == 1 ? -x[IX(data.N - 2, j)] : x[IX(data.N - 2, j)];
	}

	x[IX(0, 0)] = 0.5f * (x[IX(1, 0)] + x[IX(0, 1)]);
	x[IX(0, data.N - 1)] = 0.5f * (x[IX(1, data.N - 1)] + x[IX(0, data.N - 2)]);
	x[IX(data.N - 1, 0)] = 0.5f * (x[IX(data.N - 2, 0)] + x[IX(data.N - 1, 1)]);
	x[IX(data.N - 1, data.N - 1)] = 0.5f * (x[IX(data.N - 2, data.N - 1)] + x[IX(data.N - 1, data.N - 2)]);
}

#undef IX
#undef SWAP
#undef FOR_EACH_CELL
#undef END_FOR