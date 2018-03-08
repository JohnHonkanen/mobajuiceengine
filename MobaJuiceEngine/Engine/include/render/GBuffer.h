#pragma once
#include <map>
class GBuffer {
	using uint = unsigned int;
public:
	enum GBUFFER_TEXTURE_TYPE {
		GBUFFER_TEXTURE_TYPE_POSITION,
		GBUFFER_TEXTURE_TYPE_DIFFUSE,
		GBUFFER_TEXTURE_TYPE_NORMAL,
		GBUFFER_TEXTURE_TYPE_TEXCOORD,
		GBUFFER_NUM_TEXTURES
	};

	enum TEXTURE_TYPE
	{
		POSITION, NORMAL, ALBEDOSPEC, EMISSION, RBO_DEPTH
	};

	GBuffer(unsigned int width, unsigned int height);
	void Init();
	void BindForWriting();
	void BindForReading();
	void SetReadBuffer(GBUFFER_TEXTURE_TYPE TextureType);

	std::map<TEXTURE_TYPE,uint> GetTextures() const;

private:
	uint gBuffer;
	std::map<TEXTURE_TYPE,uint> textures;
	uint width, height;
};