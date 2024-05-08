#include "SingleThreadWorld.h"

SingleThreadWorld::SingleThreadWorld(sf::Vector2<double> size): World(size){}

void SingleThreadWorld::merge(int bigger, int smaller) {

    objects[bigger].setVelocity((objects[bigger].getVelocity() * objects[bigger].getMass() + objects[smaller].getVelocity() * objects[smaller].getMass()) /
                                      (objects[bigger].getMass() + objects[smaller].getMass()));

    objects[bigger].setPosition((objects[bigger].getPosition() * objects[bigger].getMass() + objects[smaller].getPosition() * objects[smaller].getMass()) /
                          (objects[bigger].getMass() + objects[smaller].getMass()));

    objects[bigger].setMass(objects[bigger].getMass()+objects[smaller].getMass());


    objects[smaller].setMass(0);
    objects[smaller].setVelocity(sf::Vector2<double>(0,0));
    objects[smaller].setPosition(sf::Vector2<double>(0,0));
}

void SingleThreadWorld::collision(int i, int j, sf::Vector2<double> tang) {
    sf::Vector2<double> normal = sf::Vector2<double>(tang.y, -tang.x);
    sf::Vector2<double> newVelocity = (objects[j].getVelocity().x*tang.x+objects[j].getVelocity().y*tang.y)*tang +
        (objects[i].getVelocity().x*normal.x+objects[i].getVelocity().y*normal.y)*normal;

    objects[i].setVelocity(sf::Vector2<double>(newVelocity));

    newVelocity = (objects[i].getVelocity().x*tang.x+objects[i].getVelocity().y*tang.y)*-1*tang +
        (objects[j].getVelocity().x*normal.x+objects[j].getVelocity().y*normal.y)*normal;
    objects[j].setVelocity(newVelocity);
}



void SingleThreadWorld::Tick(double elapsedSec) {
#pragma omp parallel for
    for (int i = 0; i < objects.size(); ++i) {
        sf::Vector2<double> force{0, 0};
#pragma omp parallel for
        for (int j = 0; j < objects.size(); ++j) {
            if (i == j) {
                continue;
            }
            sf::Vector2<double> delta = objects[j].getPosition() - objects[i].getPosition();
            double dist = std::sqrt(delta.x * delta.x + delta.y * delta.y);
            //double dist = std::max(std::sqrt(delta.x * delta.x + delta.y * delta.y),std::min(objects[i].getRadius(), objects[j].getRadius()));
            force += delta/dist * objects[i].getMass() * objects[j].getMass() / std::pow(dist, 2)  * G;
            if (dist <= objects[i].getRadius() && objects[i].getMass() > objects[j].getMass())
                merge(i, j);
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
