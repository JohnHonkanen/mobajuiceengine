#pragma once

namespace Engine
{
	namespace HUD {
		struct HUDRect
		{
			HUDRect() {};
			HUDRect(float _x, float _y, float _width, float _height) {
				x = _x;
				y = _y;
				width = _width;
				height = _height;
			}
			float x, y;
			float width, height;

			//Only adds position values
			HUDRect operator+(HUDRect rect) {
				return { x + rect.x, y + rect.y, width, height };
			}
		};
	}
}
