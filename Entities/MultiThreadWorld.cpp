#include "MultiThreadWorld.h"

MultiThreadWorld::MultiThreadWorld(sf::Vector2<double> size)
    : World(size)
{
    std::cout << std::thread::hardware_concurrency() << " threads will be used" << std::endl;
}

void MultiThreadWorld::merge(int bigger, int smaller) {

    objects[bigger].setVelocity((objects[bigger].getVelocity() * objects[bigger].getMass() + objects[smaller].getVelocity() * objects[smaller].getMass()) /
                                      (objects[bigger].getMass() + objects[smaller].getMass()));

    objects[bigger].setPosition((objects[bigger].getPosition() * objects[bigger].getMass() + objects[smaller].getPosition() * objects[smaller].getMass()) /
                          (objects[bigger].getMass() + objects[smaller].getMass()));

    objects[bigger].setMass(objects[bigger].getMass()+objects[smaller].getMass());


    objects[smaller].setMass(0);
    objects[smaller].setVelocity(sf::Vector2<double>(0,0));
    objects[smaller].setPosition(sf::Vector2<double>(0,0));
}

void MultiThreadWorld::Tick(double elapsedSec) {
    std::atomic<size_t> tasksPending = objects.size();

    unsigned int workersNum = std::thread::hardware_concurrency() - 1;

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
                double dist = std::max(std::sqrt(delta.x * delta.x + delta.y * delta.y), 1.);
                force += delta/dist * objects[i].getMass() * objects[j].getMass() / std::pow(dist, 2)  * G;
                if (dist <= objects[i].getRadius() && objects[i].getMass() > objects[j].getMass())
                    merge(i, j);
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
