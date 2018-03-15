#pragma once
#include <vector>

class FrameBuffer
{
	using uint = unsigned int;
public:
	FrameBuffer(uint width, uint height, uint attachmentCount, bool depthMap = false);

	void Init();
	void BindForWriting();
	void BindForWriting(unsigned int index);
	void BindForReading();

	//Read Only FrameBuffer Texture
	std::vector<uint> GetTextures() const;
	uint GetHeight() const;
	uint GetWidth() const;

private:
	uint fbo;
	uint depthBuffer;
	uint width, height;
	bool depthMap = false;

	const uint SHADOW_WIDTH = 1024, SHADOW_HEIGHT = 1024;
	std::vector<uint> textureBuffer;
};