#include <SFML/Graphics.hpp>
#include "Simulator.h"
#include "Particle.h"
#include <iostream>

int main() {
    // Create the main window
    sf::RenderWindow window(sf::VideoMode(1200, 700), "SFML window");
    
    // Set the framerate
    //window.setFramerateLimit(240);

    // Simulator
    Simulator simulator;

    // Dela Time
    sf::Clock clock;
    sf::Time elapsed = clock.restart();
    float dt = elapsed.asSeconds();

    // Start the game loop
    while (window.isOpen()) {

        // Process events
        sf::Event event;
        while (window.pollEvent(event)) {
            // Close window: exit
            if (event.type == sf::Event::Closed)
                window.close();
        }

        // Calculate Delta Time
        elapsed = clock.restart();
        dt = elapsed.asSeconds();
        std::cout << "FPS: " << 1.0f / dt << std::endl;

        // Update the game
        simulator.update(dt);

        // Clear screen
        window.clear();

        // Draw stuff
        simulator.draw(window);

        // Update the window
        window.display();
    }

    return EXIT_SUCCESS;
}