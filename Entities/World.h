#pragma once
#include <SFML/Graphics.hpp>
#include "Object.h"
#include "../misc/ext_math.h"



class World {
public:
    World(sf::Vector2<double> size);
    virtual ~World() = default;

    void GenerateObjects(int objectsNumber);
    virtual void Tick(double elapsedSec) = 0;
    void Render(sf::RenderWindow& window);
    void merge(int bigger, int smaller, double dist);
    void collision(int i, int j, double dist);

private:
    sf::Vector2<double> _worldSize;


public:
    std::vector<Object> objects;

    static constexpr double G = 10;
};


