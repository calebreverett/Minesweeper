#include "Support.h"
#include <ctime>

unordered_map<string, sf::Texture> Textures::textures;

void Textures::loadTexture(string textureName) {
    string path = "images/";
    path += textureName;
    path += ".png";

    textures[textureName].loadFromFile(path);
}

sf::Texture &Textures::GetTexture(string textureName) {
    if(textures.find(textureName) == textures.end()){
        loadTexture(textureName);
    }
    return textures[textureName];
}

void Textures::Clear() {
    textures.clear();
}

std::mt19937 Random::random(time(0));

int Random::Int(int min, int max) {
    std::uniform_int_distribution<int> dist(min, max);
    return dist(random);
}

float Random::Float(float min, float max) {
    std::uniform_real_distribution<float> dist(min, max);
    return dist(random);
}