#include "Rectangle.h"
#include <Logger.h>
#include <Globals.h>

StaticTile::StaticTile()
{
	
}

void StaticTile::Start()
{
}

void StaticTile::Update(float deltaTime)
{
	
}

void StaticTile::Destroy()
{

}

bool StaticTile::SetTexture(const TextureData& textureData)
{
	rectangle.setSize(sf::Vector2f(100, 100));

	rectangle.setTexture(&textureData.Texture);

	return true;
}

bool StaticTile::SetStaticTile(const StaticTileData& staticData)
{
	rectangle.setTextureRect({ {staticData.StartX, staticData.StartY}, {staticData.SizeX, staticData.SizeY} });
	return false;
}

bool StaticTile::SetTextureAndStaticTile(const std::string& textureName, const std::string& staticTileName)
{
	const TextureData& textureData = gData.TextureMgr->GetTextureData(textureName);

	const StaticTileData& staticTileData = textureData.StaticTilesData.at(staticTileName);

	SetTexture(textureData);
	SetStaticTile(staticTileData);

	Drawable = &rectangle;

	return false;
}
