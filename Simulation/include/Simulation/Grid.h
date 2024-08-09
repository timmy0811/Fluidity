#pragma once

#include "Log.h"

#include <memory>

namespace Simulation {
	struct GridDto {
		bool hasChanged = false;
		bool hasChangedDim = false;
		unsigned w, h;
		float* mat;

		~GridDto() {
			// Belongs to GridData
			// free(mat);
		}
	};

	struct GridData {
		int N = 62;
		size_t size;

		float dt = 0.1f, diff = 0.f, visc = 0.f;
		float force, source;

		float* u, * v, * u_prev, * v_prev;
		float* dens, * dens_prev;

		GridData() = default;
		~GridData() { release(); }

		void release() {
			free(u); free(v);
			free(u_prev); free(v_prev);
			free(dens);	free(dens_prev);
		}

		void clear() {
			size = std::pow((N + 2), 2.0);

			memset(u, 0, size);
			memset(v, 0, size);
			memset(u_prev, 0, size);
			memset(v_prev, 0, size);
			memset(dens, 0, size);
			memset(dens_prev, 0, size);
		}

		bool resize(int resolution) {
			N = resolution;
			size = std::pow((N + 2), 2);

			float* u_t = (float*)realloc(u, size * sizeof(float));
			float* v_t = (float*)realloc(v, size * sizeof(float));
			float* u_prev_t = (float*)realloc(u_prev, size * sizeof(float));
			float* v_prev_t = (float*)realloc(v_prev, size * sizeof(float));
			float* dens_t = (float*)realloc(dens, size * sizeof(float));
			float* dens_prev_t = (float*)realloc(dens_prev, size * sizeof(float));

			if (!u_t || !v_t || !u_prev_t || !v_prev_t || !dens_t || !dens_prev_t) {
				LOG_SIM_ERROR("Cannot reallocate memory for resizing of simulation data");
				__debugbreak();

				return false;
			}

			u = u_t;
			v = v_t;
			u_prev = u_prev_t;
			v_prev = v_prev_t;
			dens = dens_t;
			dens = dens_prev_t;

			return true;
		}

		bool allocate() {
			size = std::pow((N + 2), 2);

			u = (float*)malloc(size * sizeof(float));
			v = (float*)malloc(size * sizeof(float));
			u_prev = (float*)malloc(size * sizeof(float));
			v_prev = (float*)malloc(size * sizeof(float));
			dens = (float*)malloc(size * sizeof(float));
			dens_prev = (float*)malloc(size * sizeof(float));

			if (!u || !v || !u_prev || !v_prev || !dens || !dens_prev) {
				LOG_SIM_ERROR("Cannot allocate simulation data");
				__debugbreak();

				return false;
			}

			return true;
		}
	};
}