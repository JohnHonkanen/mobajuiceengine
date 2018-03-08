#include "render\GBuffer.h"
#include <GL\glew.h>
GBuffer::GBuffer(unsigned int width, unsigned int height) :
	width(width), height(height)
{

}

void GBuffer::Init()
{
	glGenFramebuffers(1, &gBuffer);
	glBindFramebuffer(GL_DRAW_FRAMEBUFFER, gBuffer);

	//Loop through our Enums to configure GBUFFER Textures
	for (int enumV = POSITION; enumV != EMISSION; enumV++)
	{
		TEXTURE_TYPE type = static_cast<TEXTURE_TYPE>(enumV);

		glGenTextures(1, &textures[type]);
		glBindTexture(GL_TEXTURE_2D, textures[type]);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB16F, width, height, 0, GL_RGBA, GL_FLOAT, NULL);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0 + enumV, GL_TEXTURE_2D, textures[type], 0);
	}

	unsigned int attachments[4] = { GL_COLOR_ATTACHMENT0, GL_COLOR_ATTACHMENT1, GL_COLOR_ATTACHMENT2, GL_COLOR_ATTACHMENT3 };
	glDrawBuffers(4, attachments);

	glGenRenderbuffers(1, &textures[RBO_DEPTH]);
	glBindRenderbuffer(GL_RENDERBUFFER, textures[RBO_DEPTH]);
	glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT, width, height);
	glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, textures[RBO_DEPTH]);

	//Check if framebuffer is complete
	if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE) {
		printf("Framebuffer is not complete");
	}

	glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

void GBuffer::BindForWriting()
{
	glBindFramebuffer(GL_DRAW_FRAMEBUFFER, gBuffer);
}

void GBuffer::BindForReading()
{
	glBindFramebuffer(GL_READ_FRAMEBUFFER, gBuffer);
}

void GBuffer::SetReadBuffer(GBUFFER_TEXTURE_TYPE TextureType)
{
	glReadBuffer(GL_COLOR_ATTACHMENT0 + TextureType);
}

std::map<GBuffer::TEXTURE_TYPE, GBuffer::uint> GBuffer::GetTextures() const
{
	return std::map<TEXTURE_TYPE, uint>(textures.begin(), textures.end());
}
