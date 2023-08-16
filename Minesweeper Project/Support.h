#include <SFML/Graphics.hpp>
#include <unordered_map>
#include <string>
#include <random>

using std::unordered_map;
using std::string;

class Textures {
    static unordered_map<std::string, sf::Texture> textures;

public:
    static void loadTexture(string textureName);
    static sf::Texture& GetTexture(string textureName);
    static void Clear();
};

class Random{
    static std::mt19937 random;

public:
    static int Int(int min, int max);
    static float Float(float min, float max);

};
