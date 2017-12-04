#pragma once
#include "components/Component.h"
#include "components/Tile.h"
#include "core\GameEngine.h"
#include "components/Camera.h"
#include <cereal\cereal.hpp>
#include <cereal\types\polymorphic.hpp>
#include <GL\glew.h>
#include <vector>
#include <glm\glm.hpp>
#include <glm\gtc\type_ptr.hpp>


using namespace std;
using namespace glm;

namespace Engine {
	class GridRender : public Component {
	private:
		Tile* tile;
		int gridWidth, gridHeight;
		float cellSize, planeHeight;
		vector<float> verticies;
		GLuint VBO, VAO;

		void GridSetup();

	public:

		template<class Archive>
		void serialize(Archive & ar)
		{
		}

		/*default constructor*/
		GridRender();
		/*destructor*/
		~GridRender();
		static GridRender* Create(GameObject * gameObjecth);
		/*
		Draw the highlighted tile, not currently used
		*/
		virtual void Draw();
		virtual void Start();
	};
}
using namespace Engine;

#include <cereal/archives/xml.hpp>

CEREAL_REGISTER_TYPE(GridRender);

//Bind it to the Behaviour
CEREAL_REGISTER_POLYMORPHIC_RELATION(Behaviour, GridRender);