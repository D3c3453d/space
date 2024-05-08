#include "World.h"


World::World(sf::Vector2<double> size): _worldSize(size) {}


void World::Render(sf::RenderWindow &window) {
    for(Object& object : objects)
        window.draw(object.getShape());
}

void World::GenerateObjects(int objectsNumber) {
    for(int i = 0; i < objectsNumber; ++i) {
        Object object(sf::Vector2<double>(RandomDouble(0, _worldSize.x), RandomDouble(0, _worldSize.y)),
        sf::Vector2<double>(0,0),
        sf::Color(RandomInt(0,255), RandomInt(0,255), RandomInt(0,255)),
        RandomDouble(10, 100));
        this->objects.push_back(object);
    }
}
