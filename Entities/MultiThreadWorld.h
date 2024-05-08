#pragma once
#include "World.h"
#include "../misc/mpmc_queue.h"
#include <thread>
#include <iostream>





class MultiThreadWorld : public World {
    void merge(int bigger, int smaller);
public:
    MultiThreadWorld(sf::Vector2<double> size);
    void Tick(double elapsedSec) override;

private:
    using MPMCQueue = MutexMPMCQueue<size_t>;
    MPMCQueue _queue;
};


