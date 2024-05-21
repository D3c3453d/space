#include "MultiThreadWorld.h"

MultiThreadWorld::MultiThreadWorld(sf::Vector2<double> size)
    : World(size)
{
    std::cout << std::thread::hardware_concurrency() << " threads will be used" << std::endl;
}

void MultiThreadWorld::Tick(double elapsedSec) {
    std::atomic<int> tasksPending = objects.size();

    unsigned int workersNum = std::thread::hardware_concurrency();

    auto work = [&] () {
        while (tasksPending.fetch_sub(1) > 0) {
            size_t i;
            _queue.pop(i);

            sf::Vector2<double> force{0, 0};
            for (int j = 0; j < objects.size(); ++j) {
                if (i == j) {
                    continue;
                }
                sf::Vector2<double> delta = objects[j].getPosition() - objects[i].getPosition();
                //double dist = std::max(std::sqrt(delta.x * delta.x + delta.y * delta.y), 1.);
                double dist = std::max(std::sqrt(delta.x * delta.x + delta.y * delta.y),std::min(objects[i].getRadius(), objects[j].getRadius()));
                force += delta/dist * objects[i].getMass() * objects[j].getMass() / std::pow(dist, 2)  * G;
                //collision(i, j, dist);
                merge(i, j, dist);
            }
            objects[i].setVelocity(objects[i].getVelocity() + force / objects[i].getMass() * elapsedSec);
        }
    };

    for (size_t i = 0; i < objects.size(); ++i) {
        _queue.push(i);
    }

    std::vector<std::thread> threads;
    threads.resize(workersNum);

    for (size_t i = 0; i < workersNum; ++i) {
        threads[i] = std::thread(work);
    }

    for (size_t i = 0; i < workersNum; ++i) {
        threads[i].join();
    }


    for (int i = 0; i < objects.size(); ++i) {
        if(objects[i].getMass() == 0) {
            objects.erase(objects.begin()+i);
            continue;
        }
        //std::cout << "[" << i << "]" << objects.size() << " " << objects[i].getMass() << std::endl;
        objects[i].setPosition(objects[i].getPosition() + objects[i].getVelocity()*elapsedSec);
    }
}
