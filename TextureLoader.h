#pragma once
#include <SFML/Graphics.hpp>
#include <unordered_map>
#include <string>

class TextureLoader
{
public:
    static TextureLoader& getInstance()
    {
        static TextureLoader instance;
        return instance;
    }

    sf::Texture& getTexture(const std::string& textureFile)
    {
        auto it = textures.find(textureFile);
        if (it != textures.end())
            return it->second;
        else
        {
            sf::Texture texture;
            if (texture.loadFromFile(textureFile))
                textures[textureFile] = texture;
            return textures[textureFile];
        }
    }

private:
    std::unordered_map<std::string, sf::Texture> textures;

    TextureLoader() {}

    TextureLoader(const TextureLoader&) = delete;
    TextureLoader& operator=(const TextureLoader&) = delete;
};
