#pragma once
#include <SFML/Graphics.hpp>


class Camera {
private:
    sf::View view;
public:
    Camera(sf::RenderWindow& window);

    void actions(sf::RenderWindow& window, sf::Event& event);

    void background(sf::RenderWindow& window);
};


