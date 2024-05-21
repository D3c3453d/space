#pragma once
#include "World.h"
#include "../misc/mpmc_queue.h"
#include <thread>
#include <iostream>





class MultiThreadWorld : public World {
public:
    MultiThreadWorld(sf::Vector2<double> size);
    void Tick(double elapsedSec) override;

private:
    using MPMCQueue = MutexMPMCQueue<size_t>;
    MPMCQueue _queue;
};


