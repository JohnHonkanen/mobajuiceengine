#include "render\FrameBuffer.h"
#include <GL\glew.h>

FrameBuffer::FrameBuffer(uint width, uint height, uint attachmentCount, bool depthMap) : 
	width(width), height(height), depthMap(depthMap)
{
	textureBuffer.resize(attachmentCount);
}

void FrameBuffer::Init()
{
	glGenFramebuffers(1, &fbo);
	glBindFramebuffer(GL_DRAW_FRAMEBUFFER, fbo);

	glGenTextures(textureBuffer.size(), &textureBuffer[0]);

	if (depthMap == true) {
		for (unsigned int i = 0; i < textureBuffer.size(); i++)
		{
			glBindTexture(GL_TEXTURE_2D, textureBuffer[i]);
			glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT, SHADOW_WIDTH, SHADOW_HEIGHT, 0, GL_DEPTH_COMPONENT, GL_FLOAT, nullptr);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_COMPARE_MODE, GL_NONE);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);
		}
		

		// attach depth texture as FBO's depth buffer
		glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, textureBuffer[0], 0);

		// we only need the depth information when rendering the scene from the light's perspective, so there is no need for a color buffer to render any color data.
		glDrawBuffer(GL_NONE);
		glReadBuffer(GL_NONE);

	}
	else
	{
		std::vector<uint> attachments;
		attachments.resize(textureBuffer.size());

		for (int i = 0; i < textureBuffer.size(); i++) {

			glBindTexture(GL_TEXTURE_2D, textureBuffer[i]);
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA32F, width, height, 0, GL_RGBA, GL_FLOAT, nullptr);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
			glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0 + i, GL_TEXTURE_2D, textureBuffer[i], 0);

			// tell OpenGL which color attachments we'll use (of this framebuffer) for rendering 
			attachments[i] = GL_COLOR_ATTACHMENT0 + i;
		}

		glDrawBuffers(textureBuffer.size(), &attachments[0]);
		glGenRenderbuffers(1, &depthBuffer);
		glBindRenderbuffer(GL_RENDERBUFFER, depthBuffer);
		glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT, width, height);
		glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, depthBuffer);
	}

	//Check if framebuffer is complete
	if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE) {
		printf("Framebuffer is not complete");
	}

	glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

void FrameBuffer::BindForWriting()
{
	glBindFramebuffer(GL_DRAW_FRAMEBUFFER, fbo);
}

void FrameBuffer::BindForWriting(unsigned int index)
{
	glBindFramebuffer(GL_DRAW_FRAMEBUFFER, fbo);
	//glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, textureBuffer[index], 0);
}

void FrameBuffer::BindForReading()
{
	if (depthMap)
	{
		for (int i = 0; i < textureBuffer.size(); i++) {
			glActiveTexture(GL_TEXTURE0 + i);
			glBindTexture(GL_TEXTURE_2D, textureBuffer[i]);
		}
	}
	else {
		glBindFramebuffer(GL_READ_FRAMEBUFFER, fbo);
	}
	
}

std::vector<FrameBuffer::uint> FrameBuffer::GetTextures() const
{
	return std::vector<uint>(textureBuffer.begin(), textureBuffer.end());
}

FrameBuffer::uint FrameBuffer::GetHeight() const
{
	return height;
}

FrameBuffer::uint FrameBuffer::GetWidth() const
{
	return width;
}
