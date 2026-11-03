#include "Sprite.h"
#include <Logger.h>
#include <Globals.h>

Sprite::Sprite(int x, int y) : IDrawable(x, y), sprite(texture)
{
	
}

void Sprite::Start()
{

}
void Sprite::Update(float deltaTime)
{
	if (data == nullptr)
	{
		return;
	}
	
	if (data->TimeBetweenAnimationInS == 0)
	{
		return;
	}

	elapsedTime += deltaTime;

	if (elapsedTime >= data->TimeBetweenAnimationInS)
	{
		spriteCount++;

		if (spriteCount > data->SpriteOnLine)
		{
			spriteCount = 1;
		}

		int count = spriteCount;

		sprite.setTextureRect({ {data->StartX + ((count - 1) * (data->OffsetX + data->SizeX)), data->StartY},
			{data->SizeX, data->SizeY}});

		elapsedTime = 0;
	}
}

void Sprite::Destroy()
{

}

bool Sprite::SetSpriteData()
{
	sprite.setTextureRect({ {data->StartX, data->StartY}, { data->SizeX, data->SizeY } });
	
	sprite.setOrigin({ static_cast<float>(data->SizeX) * (data->IsReverted ? 1 : 0), 0 });

	sprite.setScale({ data->IsReverted ? -1.f : 1.f, 1.f });

	return true;
}

bool Sprite::SetTexture(const TextureData& textureData)
{
	sprite.setTexture(textureData.Texture);
	return true;
}

bool Sprite::SetTextureAndSprite(const std::string& textureName, const std::string& spriteName)
{
	const TextureData& textureData = gData.TextureMgr->GetTextureData(textureName);

	data = &textureData.AnimationsData.at(spriteName);

	SetTexture(textureData);
	SetSpriteData();

	Drawable = &sprite;

	return true;
}