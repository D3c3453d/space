#include "Object.h"

Object::Object(sf::Vector2<double> position, sf::Vector2<double> velocity, sf::Color color, double mass)
    : velocity(velocity)
    , mass(mass)
    , radius(std::sqrt(mass)/density)
    , position(position)
{
    shape.setFillColor(color);
    shape.setRadius(this->radius);
    shape.setPosition(sf::Vector2f(this->position-sf::Vector2<double>(radius, radius)));
}
// SETTERS
void Object::setPosition(sf::Vector2<double> position) {
    this->position = position;
    shape.setPosition(sf::Vector2f(this->position-sf::Vector2<double>(radius, radius)));
}

void Object::setVelocity(sf::Vector2<double> velocity) {
    this->velocity = velocity;
}
void Object::setMass(double mass) {
    this->mass = mass;
    this->radius = std::sqrt(mass)/density;
    shape.setRadius(this->radius);
}
// GETTERS
sf::Vector2<double> Object::getPosition() {
    return this->position;
}

sf::Vector2<double> Object::getVelocity() {
    return this->velocity;
}

double Object::getMass() {
    return this->mass;
}

double Object::getRadius() {
    return this->radius;
}

sf::CircleShape Object::getShape() {
    return this->shape;
}
