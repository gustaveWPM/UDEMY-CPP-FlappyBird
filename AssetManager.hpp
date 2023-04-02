#pragma once

#include <string>
#include <unordered_map>

#include <SFML/Graphics.hpp>

namespace FlappyBirdEngine {
    class AssetManager {
    public:
        AssetManager() {}
        ~AssetManager() {}

        void loadTexture(std::string name, std::string fileName);
        sf::Texture& getTexture(std::string name);

        void loadFont(std::string name, std::string fileName);
        sf::Font& getFont(std::string name);

    private:
        std::unordered_map<std::string, sf::Texture> _textures;
        std::unordered_map<std::string, sf::Font> _fonts;
    };
}