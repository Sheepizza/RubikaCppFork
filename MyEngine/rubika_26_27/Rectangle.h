#pragma once

#include <SFML/Graphics/RectangleShape.hpp>
#include <IDrawable.h>
#include <TextureMgr.h>

class StaticTile : public IDrawable
{
public:
	sf::RectangleShape rectangle;

	StaticTile();

	void Start();
	void Update(float deltaTime);
	void Destroy();

	bool SetTextureAndStaticTile(const std::string& textureName, const std::string& staticTileName);


private:
	bool SetTexture(const TextureData& textureData);
	bool SetStaticTile(const StaticTileData& staticData);
};

