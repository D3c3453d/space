#pragma once
#include "World.h"
#include <omp.h>
#include <cmath>
#include <iostream>


class OmpWorld : public World {
public:
    OmpWorld(sf::Vector2<double> size);
    void Tick(double elapsedSec) override;
};