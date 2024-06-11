#include <SFML/Graphics.hpp>
#include "Constants.h"
#include "Simulator.h"
#include "Particle.h"
#include <random>
#include <iostream>
#include <cmath>

// Constructor
Simulator::Simulator(): particles(nullptr), boundingBox(nullptr) {
    // Game Variables and Constants
    this->particles = new Particle[NUM_PARTICLES];
    
    // Set random velocities
    std::random_device rd;  //Will be used to obtain a seed for the random number engine
    std::mt19937 gen(rd()); //Standard mersenne_twister_engine seeded with rd()
    std::uniform_real_distribution<> dis(-1.0, 1.0);
    std::uniform_real_distribution<> dis2(0.0, 1.0);

    for (int i = 0; i < NUM_PARTICLES; i++) {
        this->particles[i].setVelocity(100.0f * dis(gen), 100.0f * dis(gen));
        this->particles[i].setPosition(LEFT_BOUND + BALL_RADIUS + (SCREEN_WIDTH - LEFT_BOUND * 2 - BALL_RADIUS) * dis2(gen), BOTTOM_BOUND + BALL_RADIUS + (SCREEN_HEIGHT - BOTTOM_BOUND * 2 - BALL_RADIUS) * dis2(gen));
    }

    // Bounding Box
    this->boundingBox = new sf::RectangleShape[4]
        {sf::RectangleShape(sf::Vector2f(SCREEN_WIDTH - LEFT_BOUND * 2, 5)), 
        sf::RectangleShape(sf::Vector2f(SCREEN_WIDTH - LEFT_BOUND * 2, 5)), 
        sf::RectangleShape(sf::Vector2f(5, SCREEN_HEIGHT - BOTTOM_BOUND * 2)), 
        sf::RectangleShape(sf::Vector2f(5, SCREEN_HEIGHT - BOTTOM_BOUND * 2))};

    this->boundingBox[0].setPosition(LEFT_BOUND, SCREEN_HEIGHT - (TOP_BOUND + 5));
    this->boundingBox[1].setPosition(LEFT_BOUND, SCREEN_HEIGHT - BOTTOM_BOUND);
    this->boundingBox[2].setPosition(LEFT_BOUND - 5, SCREEN_HEIGHT - TOP_BOUND);
    this->boundingBox[3].setPosition(RIGHT_BOUND, SCREEN_HEIGHT - TOP_BOUND);
}

// Destructor
Simulator::~Simulator() {
    delete[] this->particles;
    delete[] this->boundingBox;
}

// Functions
void Simulator::update(float &dt) {
    // Update the game
    for (int i = 0; i < NUM_PARTICLES; i++) {
        this->particles[i].update(dt);
    }

    // Check for collisions
    for (int i = 0; i < NUM_PARTICLES; i++) {
        Particle &p = this->particles[i];
        for (int j = i + 1; j < NUM_PARTICLES; j++) {
            Particle &p2 = this->particles[j];
            float dx = p2.getXPos() - p.getXPos();
            float dy = p2.getYPos() - p.getYPos();
            float distance = sqrt(dx * dx + dy * dy);
            if (distance < p.getRadius() + p2.getRadius()) {
                float angle = atan2(dy, dx);
                float overlap = p.getRadius() + p2.getRadius() - distance;
                p.setPosition(p.getXPos() - cos(angle) * overlap / 2, p.getYPos() - sin(angle) * overlap / 2);
                p2.setPosition(p2.getXPos() + cos(angle) * overlap / 2, p2.getYPos() + sin(angle) * overlap / 2);
                float dp1 = p.getVelocityX() * cos(angle) + p.getVelocityY() * sin(angle);
                float dp2 = p2.getVelocityX() * cos(angle) + p2.getVelocityY() * sin(angle);
                float m1 = p.getRadius() * p.getRadius();
                float m2 = p2.getRadius() * p2.getRadius();
                float momentum = 2 * (dp1 - dp2) / (m1 + m2);
                p.setVelocity(p.getVelocityX() - momentum * m2 * cos(angle) * ELASTICITY2, p.getVelocityY() - momentum * m2 * sin(angle) * ELASTICITY2);
                p2.setVelocity(p2.getVelocityX() + momentum * m1 * cos(angle) * ELASTICITY2, p2.getVelocityY() + momentum * m1 * sin(angle) * ELASTICITY2);
            }
        }
    }
}

void Simulator::draw(sf::RenderWindow &window) {
    for (int i = 0; i < NUM_PARTICLES; i++) {
        particles[i].draw(window);
    }
    
    for (int i = 0; i < 4; i++) {
        window.draw(boundingBox[i]);
    }
}