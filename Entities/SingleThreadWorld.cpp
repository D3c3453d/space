#include "SingleThreadWorld.h"
#include <cstdlib>
#include <cmath>

SingleThreadWorld::SingleThreadWorld(sf::Vector2<double> size): World(size){}


void SingleThreadWorld::Tick(double elapsedSec) {
    for (int i = 0; i < objects.size(); ++i) {
        sf::Vector2<double> force{0, 0};
        for (int j = 0; j < objects.size(); ++j) {
            if (i == j) {
                continue;
            }
            sf::Vector2<double> delta = objects[j].getPosition() - objects[i].getPosition();
            //double dist = std::sqrt(delta.x * delta.x + delta.y * delta.y);
            double dist = std::max(std::sqrt(delta.x * delta.x + delta.y * delta.y),std::min(objects[i].getRadius(), objects[j].getRadius()));
            force += delta/dist * objects[i].getMass() * objects[j].getMass() / std::pow(dist, 2)  * G;
            collision(i, j, dist);
            //merge(i, j, dist);
        }
        objects[i].setVelocity(objects[i].getVelocity() + force / objects[i].getMass() * elapsedSec);
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
