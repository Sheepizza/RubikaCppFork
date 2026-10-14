#include <rapidxml/rapidxml.hpp>
#include <rapidxml/rapidxml_utils.hpp>

#include "TextureMgr.h"
#include "Logger.h"

using namespace rapidxml;

TextureData::TextureData()
{
}

TextureData::~TextureData()
{
}

void TextureMgr::Init()
{
	LoadTexture("../Ressources/IsaacSprite");
	CreateDefaultTexture();
}

void TextureMgr::Shut()
{

}

bool TextureMgr::LoadTexture(const std::filesystem::path& path)
{
	TextureData textureData = TextureData();

	std::string dataPath = path.string() += ".xml";
	
	if (!std::filesystem::exists(dataPath))
	{
		Logger::Error(std::format("{}.xml doesn't exist.", path.filename().string()));
		return false;
	}

	file<> f = file(dataPath.c_str());
	xml_document<> doc;

	doc.parse<0>(f.data());

	xml_node<>* root = doc.first_node();

	std::string rootName = std::string(root->name());

	if (rootName == "Animations")
	{
		for (xml_node<>* node = root->first_node(); node; node = node->next_sibling())
		{
			AnimationData data = LoadAnimationData(node);
			textureData.AnimationsData.emplace(node->first_attribute()->value(), data);
		}
	}

	std::string texturePath = path.string() += ".png";

	if (!std::filesystem::exists(texturePath))
	{
		Logger::Error(std::format("{}.png doesn't exist.", path.filename().string()));
		return false;
	}

	sf::Texture texture(texturePath);

	textureData.Texture = texture;

	TexturesData.emplace(path.filename().string(), textureData);

	return false;
}

AnimationData TextureMgr::LoadAnimationData(xml_node<>* root)
{
	AnimationData* data = new AnimationData();

	for (xml_node<>* childNode = root->first_node(); childNode; childNode = childNode->next_sibling())
	{
		std::string name = childNode->name();

		if (name == "X")
		{
			data->StartX = std::stoi(childNode->value());
		}
		else if (name == "Y")
		{
			data->StartY = std::stoi(childNode->value());
		}
		else if (name == "SizeX")
		{
			data->SizeX = std::stoi(childNode->value());
		}
		else if (name == "SizeY")
		{
			data->SizeY = std::stoi(childNode->value());
		}
		else if (name == "OffsetX")
		{
			data->OffsetX = std::stoi(childNode->value());
		}
		else if (name == "OffsetY")
		{
			data->OffsetY = std::stoi(childNode->value());
		}
		else if (name == "SpriteNum")
		{
			data->AnimationSpriteCount = std::stoi(childNode->value());
		}
		else if (name == "SpriteOnLine")
		{
			data->SpriteOnLine = std::stoi(childNode->value());
		}
		else if (name == "Reverted")
		{
			data->IsReverted = std::stoi(childNode->value()) == 1;
		}
		else if (name == "TimeBetweenAnimation")
		{
			data->TimeBetweenAnimationInS = std::stof(childNode->value());
		}
	}

	return *data;
}

const TextureData& TextureMgr::GetTextureData(const std::string& name) const
{
	if (TexturesData.contains(name)) 
	{
		return TexturesData.at(name);
	}

	return TexturesData.at("Default");
}

void TextureMgr::CreateDefaultTexture()
{
	TextureData defaultData = TextureData();

	sf::Texture defaultTexture;

	defaultTexture.resize({100,100});

	defaultData.Texture = defaultTexture;

	TexturesData.emplace("Default", defaultData);
}
