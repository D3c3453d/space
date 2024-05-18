#pragma once
#include "World.h"
#include <omp.h>
#include <cmath>
#include <iostream>


class OmpWorld : public World {
    void merge(int bigger, int smaller);
    void collision(int i, int j, sf::Vector2<double> normal);
public:
    OmpWorld(sf::Vector2<double> size);
    void Tick(double elapsedSec) override;
};