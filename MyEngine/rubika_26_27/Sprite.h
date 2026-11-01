#pragma once

#include <SFML/Graphics.hpp>
#include <IDrawable.h>
#include <TextureMgr.h>

class Sprite : public IDrawable
{
public:

	sf::Sprite sprite;
	sf::Texture texture;

	Sprite();

	void Start();
	void Update(float deltaTime);
	void Destroy();

	bool SetTextureAndSprite(const std::string& textureName, const std::string& spriteName);

private:
	bool SetTexture(const TextureData& textureData);
	bool SetSpriteData();

	float elapsedTime = 0;

	int spriteCount = 0;

	const AnimationData* data = nullptr;
};

