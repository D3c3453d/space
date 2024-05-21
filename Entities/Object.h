#pragma once
#include <SFML/Graphics.hpp>
#include <cmath>


class Object {
    sf::Vector2<double> position;
    sf::Vector2<double> velocity;
    sf::CircleShape shape;
    double mass;
    double radius;
    static constexpr double density = 1;

public:
    Object(sf::Vector2<double> position, sf::Vector2<double> velocity, sf::Color color, double mass);

    void setPosition(sf::Vector2<double> position);
    void setVelocity(sf::Vector2<double> velocity);
    void setMass(double mass);

    sf::Vector2<double> getPosition();
    sf::Vector2<double> getVelocity();
    double getMass();
    double getRadius();
    sf::CircleShape getShape();
};

