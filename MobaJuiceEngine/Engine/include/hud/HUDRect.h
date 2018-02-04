#pragma once
#include <glm\glm.hpp>
#include <stdio.h>
using namespace std;

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
			HUDRect *parent = nullptr;
			//Only adds position values
			HUDRect operator+(HUDRect rect) {
				return { x + rect.x, y + rect.y, width, height };
			}

			//Move to source
			//Check if point is contained within the rect
			bool Contains(float px, float py)
			{
				//Parent + Our position
				int fx = x; 
				int fy = y;

				if (parent)
				{
					fx += parent->x;
					fy += parent->y;
				}

				printf("mouseX: %i, mouseY: %i \n", px, py);
				printf("rectx: %i, recty: %i \n", fx, fy);
				if (px > fx && px < fx + width &&
					py > fy && py < fy + height)
				{
					return true;
				}

				return false;
			}

		};
	}
}
