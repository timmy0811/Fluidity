#pragma once

namespace FLD {
	enum class Button
	{
		MOUSE_LEFT,
		MOUSE_RIGHT,
		MOUSE_MIDDLE,
		MOUSE_SCROLL
	};

	struct Vec2 {
		int x, y;
	};

	struct ButtonPressEvent {
		Button button;
		Vec2 pos;
	};
}