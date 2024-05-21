#include "World.h"


World::World(sf::Vector2<double> size): _worldSize(size) {}


void World::Render(sf::RenderWindow &window) {
    for(Object& object : objects)
        window.draw(object.getShape());
}

void World::GenerateObjects(int objectsNumber) {
    for(int i = 0; i < objectsNumber; ++i) {
        Object object(sf::Vector2<double>(RandomDouble(0, _worldSize.x), RandomDouble(0, _worldSize.y)),
        sf::Vector2<double>(RandomInt(-100,100), RandomInt(-100,100)),
        sf::Color(RandomInt(0,255), RandomInt(0,255), RandomInt(0,255)),
        RandomDouble(10, 100));
        this->objects.push_back(object);
    }
}

void World::merge(int bigger, int smaller, double dist) {
    if (dist <= objects[bigger].getRadius() && objects[bigger].getMass() > objects[smaller].getMass()) {
        objects[bigger].setVelocity((objects[bigger].getVelocity() * objects[bigger].getMass() + objects[smaller].getVelocity() * objects[smaller].getMass()) /
                                          (objects[bigger].getMass() + objects[smaller].getMass()));

        objects[bigger].setPosition((objects[bigger].getPosition() * objects[bigger].getMass() + objects[smaller].getPosition() * objects[smaller].getMass()) /
                              (objects[bigger].getMass() + objects[smaller].getMass()));

        objects[bigger].setMass(objects[bigger].getMass()+objects[smaller].getMass());


        objects[smaller].setMass(0);
        objects[smaller].setVelocity(sf::Vector2<double>(0,0));
        objects[smaller].setPosition(sf::Vector2<double>(0,0));
    }
}

void World::collision(int i, int j, double dist) {
    if (dist <= objects[i].getRadius() + objects[j].getRadius()) {
        sf::Vector2<double> deltaPosition = objects[j].getPosition() - objects[i].getPosition();
        sf::Vector2<double> deltaVelocity = objects[j].getVelocity() - objects[i].getVelocity();
        sf::Vector2<double> velocity_j = objects[j].getVelocity();
        sf::Vector2<double> velocity_i = objects[i].getVelocity();
        sf::Vector2<double> position_j = objects[j].getPosition();
        sf::Vector2<double> position_i = objects[i].getPosition();
        double absoluteDistance = sqrt((deltaPosition.x * deltaPosition.x) + (deltaPosition.y * deltaPosition.y));
        double overlap_j = objects[j].getRadius() - absoluteDistance;
        double overlap_i = objects[i].getRadius() - absoluteDistance;
        sf::Vector2<double> vectorDeltaPosition = sf::Vector2<double>(deltaPosition.x/absoluteDistance, deltaPosition.y/absoluteDistance);
        velocity_j -= ((objects[i].getMass()*2)/(objects[j].getMass() + objects[i].getMass()))*(((deltaVelocity.x*deltaPosition.x) + (deltaVelocity.y*deltaPosition.y))/(pow((deltaPosition.x),2) + pow((deltaPosition.y),2)))*deltaPosition;
        objects[j].setVelocity(velocity_j);
        deltaPosition = (-deltaPosition);
        deltaVelocity = (-deltaVelocity);
        velocity_i -= ((objects[j].getMass()*2)/(objects[j].getMass() + objects[i].getMass()))*(((deltaVelocity.x*deltaPosition.x) + (deltaVelocity.y*deltaPosition.y))/(pow((deltaPosition.x),2) + pow((deltaPosition.y),2)))*deltaPosition;
        objects[i].setVelocity(velocity_i);
    }
}
