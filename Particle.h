#ifndef PARTICLE_H
#define PARTICLE_H

#include <SFML/Graphics.hpp>

class Particle {
private:
    // Variables and Constants
    sf::CircleShape circle; // holds the sprite, radius and positions of the ball
    float velocities[2]; // holds the velocities of the ball

    void applyVelocity(float &dt);
    void checkCollision();
    void updateColor();

public:
    // Constructor
    Particle();
    Particle(float radius);
    Particle(float radius, sf::Color color, float x, float y);

    // Destructor
    ~Particle();

    // Functions
    void draw(sf::RenderWindow &window);
    void update(float &dt);
    float getXPos();
    float getYPos();
    float getVelocityX();
    float getVelocityY();
    float getRadius();
    float getMagnitude();
    void setPosition(float x, float y);
    void setVelocity(float dx, float dy);
    
};

#endif