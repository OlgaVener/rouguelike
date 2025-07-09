#include "pch.h"
#include "ResourceSystem.h"

namespace Engine
{
	ResourceSystem* ResourceSystem::Instance()
	{
		static ResourceSystem resourceSystem;
		return &resourceSystem;
	}

	void ResourceSystem::LoadTexture(const std::string& name, std::string sourcePath, bool isSmooth)
	{
		if (textures.find(name) != textures.end())
		{
			return;
		}

		sf::Texture* newTexture = new sf::Texture();
		if (newTexture->loadFromFile(sourcePath))
		{
			newTexture->setSmooth(isSmooth);
			textures.emplace(name, newTexture);
		}
	}

	const sf::Texture* ResourceSystem::GetTextureShared(const std::string& name) const
	{
		return nullptr;
	}

	sf::Texture* ResourceSystem::GetTextureCopy(const std::string& name) const
	{
		return nullptr;
	}

	void ResourceSystem::DeleteSharedTexture(const std::string& name)
	{
	}

	void ResourceSystem::LoadTextureMap(const std::string& name, std::string sourcePath, sf::Vector2u elementPixelSize, int totalElements, bool isSmooth)
	{
	}

	const sf::Texture* ResourceSystem::GetTextureMapElementShared(const std::string& name, int elementIndex) const
	{
		return nullptr;
	}

	sf::Texture* ResourceSystem::GetTextureMapElementCopy(const std::string& name, int elementIndex) const
	{
		return nullptr;
	}

	int ResourceSystem::GetTextureMapElementsCount(const std::string& name) const
	{
		return 0;
	}

	void ResourceSystem::DeleteSharedTextureMap(const std::string& name)
	{
	}

	void ResourceSystem::Clear()
	{
	}

	void ResourceSystem::DeleteAllTextures()
	{
	}

	void ResourceSystem::DeleteAllTextureMaps()
	{
	}


}
