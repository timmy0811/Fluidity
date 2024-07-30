#pragma once

#include "graphics/camera/Camera.h"

namespace FluidGL {
	class OrthographicCamera : public Camera {
	public:
		OrthographicCamera(float left, float right, float bottom, float top, float nearPlane = -1.f, float farPlane = 1.f);
	};
}