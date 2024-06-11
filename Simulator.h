#ifndef SIMULATOR_H
#define SIMULATOR_H

#include "Particle.h"
#include <SFML/Graphics.hpp>

class Simulator {
private:
    // Game Variables and Constants
    Particle *particles;
    sf::RectangleShape *boundingBox;

public:
    // Constructor
    Simulator();

    // Destructor
    ~Simulator();

    // Functions
    void update(float &dt);
    void draw(sf::RenderWindow &window);
    
};

#endif
