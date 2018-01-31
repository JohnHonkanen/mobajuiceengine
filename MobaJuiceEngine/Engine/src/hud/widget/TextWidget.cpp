#include "hud\widgets\TextWidget.h"
#include "core\GameEngine.h"
#include "render\OGLShader.h"
#include "hud\utility\Font.h"

#include "glm\gtc\type_ptr.hpp"
#include "glm\gtc\matrix_transform.hpp"

namespace Engine
{
	namespace HUD
	{
		unsigned int TextWidget::VAO = 0;	// static field is initialised
		unsigned int TextWidget::VBO = 0;	// static field is initialised

		TextWidget * TextWidget::Create(HUDElement * element, HUDRect rect, string text, string font, float scale, vec3 color)
		{
			TextWidget *w = new TextWidget(rect, text, font, scale, color);
			element->AttachWidget(w);

			return w;
		}

		TextWidget::TextWidget()
		{
		}
		TextWidget::TextWidget(HUDRect r, string text, string font, float scale, vec3 color)
			:text(text), font(font), scale(scale), color(color)
		{
			rect = r;
		}
		void TextWidget::Start()
		{
			if (VAO == 0) {
				SetupVAO();
			}
		}
		void TextWidget::Update()
		{
		}

		void TextWidget::Draw(HUD const * hud, HUDRect parent)
		{
			unsigned int shader = GameEngine::manager.shaderManager.GetShader("text");

			glUseProgram(shader);

			//Send information to shader
			glUniformMatrix4fv(glGetUniformLocation(shader, "projection"), 1, GL_FALSE, glm::value_ptr(hud->GetProjection()));
			//glUniformMatrix4fv(glGetUniformLocation(shader, "model"), 1, GL_FALSE, glm::value_ptr(model));

			glUniform3f(glGetUniformLocation(shader, "textColor"), color.x, color.y, color.z);
			glActiveTexture(GL_TEXTURE0);
			glBindVertexArray(VAO);

			//Get our character map for the font
			std::map<char, Character> characters = GameEngine::manager.fontManager.GetFont(font)->GetCharacters();
			std::string::const_iterator c;

			//Create copy of rect position
			float x, y;
			x = rect.x;
			y = rect.y;

			//Loop through our text and setup the characters
			for (c = text.begin(); c != text.end(); c++)
			{
				Character ch = characters[*c];

				GLfloat xpos = x + ch.bearing.x * scale;
				GLfloat ypos = y - (ch.size.y - ch.bearing.y) * scale;

				GLfloat w = ch.size.x * scale;
				GLfloat h = ch.size.y * scale;

				//Setup the vertices
				GLfloat vertices[6][4] = {
					{ xpos,     ypos + h,   0.0, 0.0 },
					{ xpos,     ypos,       0.0, 1.0 },
					{ xpos + w, ypos,       1.0, 1.0 },

					{ xpos,     ypos + h,   0.0, 0.0 },
					{ xpos + w, ypos,       1.0, 1.0 },
					{ xpos + w, ypos + h,   1.0, 0.0 }
				};

				glBindTexture(GL_TEXTURE_2D, ch.textureID);
				glBindBuffer(GL_ARRAY_BUFFER, VBO);
				glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices);
				glBindBuffer(GL_ARRAY_BUFFER, 0);
				//Render the quad
				glDrawArrays(GL_TRIANGLES, 0, 6);

				// Now advance cursors for next glyph (note that advance is number of 1/64 pixels)
				x += (ch.advance >> 6) * scale; // Bitshift by 6 to get value in pixels (2^6 = 64)
			}
		}

		void TextWidget::DrawWidget(unsigned int shader)
		{
		}

		void TextWidget::SetupVAO()
		{
			glGenVertexArrays(1, &VAO);
			glGenBuffers(1, &VBO);
			glBindVertexArray(VAO);
			glBindBuffer(GL_ARRAY_BUFFER, VBO);
			glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * 6 * 4, NULL, GL_DYNAMIC_DRAW);
			glEnableVertexAttribArray(0);
			glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(GLfloat), 0);
			glBindBuffer(GL_ARRAY_BUFFER, 0);
			glBindVertexArray(0);
		}
	}
}