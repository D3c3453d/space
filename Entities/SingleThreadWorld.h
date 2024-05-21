#pragma once
#include "World.h"
#include <omp.h>
#include <cmath>
#include <iostream>


class SingleThreadWorld : public World {
public:
    SingleThreadWorld(sf::Vector2<double> size);
    void Tick(double elapsedSec) override;
};