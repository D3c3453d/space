#include <SFML/Graphics.hpp>
#include "Camera.h"
#include <chrono>
#include "Entities/SingleThreadWorld.h"
#include "Entities/MultiThreadWorld.h"
#include "Entities/OmpWorld.h"

int main()
{
    sf::Vector2u windowSize(900, 900);
    sf::Vector2<double> worldSize(900, 900);
    sf::RenderWindow window(sf::VideoMode(windowSize.x, windowSize.y), "space");
    OmpWorld world(worldSize);
    //SingleThreadWorld world(worldSize);
    //MultiThreadWorld world(worldSize);
    world.GenerateObjects(1000);
    //world.objects.push_back(Object(sf::Vector2<double>(0,400), sf::Vector2<double>(200,0), sf::Color::White, 100));
    //world.objects.push_back(Object(sf::Vector2<double>(400,410), sf::Vector2<double>(-200,0), sf::Color::White, 100));
    Camera camera(window);
    using SystemClock = std::chrono::system_clock;
    using Timestamp = std::chrono::time_point<SystemClock>;
    Timestamp startTime = SystemClock::now();
    while (window.isOpen())
    {
        sf::Event event{};
        while (window.pollEvent(event))
        {
            camera.actions(window, event);

            if (event.type == sf::Event::Closed)
                window.close();

        }

        window.clear();
        Timestamp currentTime = SystemClock::now();
        int64_t elapsedUs = std::chrono::duration_cast<std::chrono::microseconds>(currentTime - startTime).count();
        float elapsedSec = 0.000001 * elapsedUs;
        world.Tick(elapsedSec);
        startTime = currentTime;
        std::cout << elapsedSec*1000 << "ms" << std::endl;
        world.Render(window);
        window.display();
    }

    return 0;
}