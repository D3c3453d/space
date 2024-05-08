#include "Camera.h"
#include <iostream>

// Constructors
Camera::Camera(sf::RenderWindow& window) {
    sf::Vector2f size = sf::Vector2f(window.getSize());
    this->view.reset(sf::FloatRect(0, 0, size.x, size. y));
    window.setView(view);
}

void Camera::actions(sf::RenderWindow& window, sf::Event& event) {
    if (event.type == sf::Event::MouseWheelMoved) {
        if(event.mouseWheel.delta == 1)
            this->view.zoom(0.9f);
        else
            this->view.zoom(1.1f);
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
        this->view.move(0, -2);
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
        this->view.move(0, 2);
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
        this->view.move(-2, 0);
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
        this->view.move(2, 0);
    }
    window.setView(this->view);
}
