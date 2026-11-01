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
	
	rectangle.setOrigin({ rectangle.getSize().x * (staticData.IsRevertedX ? 1 : 0), rectangle.getSize().y * (staticData.IsRevertedY ? 1 : 0) });

	rectangle.setScale({ staticData.IsRevertedX ? -1.f : 1.f, staticData.IsRevertedY ? -1.f : 1.f });

	return true;
}

bool StaticTile::SetTextureAndStaticTile(const std::string& textureName, const std::string& staticTileName)
{
	const TextureData& textureData = gData.TextureMgr->GetTextureData(textureName);

	const StaticTileData& staticTileData = textureData.StaticTilesData.at(staticTileName);

	SetTexture(textureData);
	SetStaticTile(staticTileData);

	Drawable = &rectangle;

	return true;
}
