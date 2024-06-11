#include <SFML/Graphics.hpp>
#include "Particle.h"
#include <iostream>
#include "Constants.h"
#include <cmath>

// Constructor
Particle::Particle(): circle(sf::CircleShape(BALL_RADIUS)) {
    // Set velocity to 0
    this->velocities[0] = 0.0f;
    this->velocities[1] = 0.0f;

    // Set the position and color of the circle
    this->circle.setOrigin(BALL_RADIUS, BALL_RADIUS);
    this->circle.setFillColor(sf::Color::Blue);
    this->circle.setPosition(0.0f, SCREEN_HEIGHT - 0.0f);
}

Particle::Particle(float radius): circle(sf::CircleShape(radius)) {
    // Set velocity to 0
    this->velocities[0] = 0.0f;
    this->velocities[1] = 0.0f;

    // Set the position and color of the circle
    this->circle.setOrigin(radius, radius);
    this->circle.setFillColor(sf::Color::Blue);
    this->circle.setPosition(0.0f, SCREEN_HEIGHT - 0.0f);
}

Particle::Particle(float radius, sf::Color color, float x, float y): circle(sf::CircleShape(radius)) {
    // Set velocity to 0
    this->velocities[0] = 0.0f;
    this->velocities[1] = 0.0f;

    // Set the position and color of the circle
    this->circle.setOrigin(radius, radius);
    this->circle.setFillColor(color);
    this->circle.setPosition(x, SCREEN_HEIGHT - y);
    
}

// Destructor
Particle::~Particle() {
    // TODO: Implement destructor
}

// Function to draw the ball on the window
void Particle::draw(sf::RenderWindow &window) {
    window.draw(this->circle);
}

// Function to update the ball's position and velocity
void Particle::update(float &dt) {
    // Update the game

    // Gravity
    if (this->velocities[1] != 0.0f && this->getYPos() + (this->velocities[1] - GRAVITY * dt) < BOTTOM_BOUND + this->getRadius() && (-GRAVITY * dt) / this->velocities[1] > 0.95f) {
        this->velocities[1] = 0.0f;
        this->setPosition(this->getXPos(), BOTTOM_BOUND + this->getRadius());
    } else if (this->velocities[1] != 0.0f) {
        this->velocities[1] -= GRAVITY * dt;
    }

    // Update the velocity
    this->applyVelocity(dt);
    this->updateColor();

    // Check for collision with the bounding box
    this->checkCollision();
    
}

void Particle::applyVelocity(float &dt) {
    this->circle.move(this->velocities[0] * dt, -this->velocities[1] * dt);
}

float Particle::getXPos() {
    return this->circle.getPosition().x;
}

float Particle::getYPos() {
    return SCREEN_HEIGHT - this->circle.getPosition().y;
}

float Particle::getRadius() {
    return this->circle.getRadius();
}

float Particle::getVelocityX() {
    return this->velocities[0];
}

float Particle::getVelocityY() {
    return this->velocities[1];
}

float Particle::getMagnitude() {
    return sqrt(this->velocities[0] * this->velocities[0] + this->velocities[1] * this->velocities[1]);
}

void Particle::setPosition(float x, float y) {
    this->circle.setPosition(x, SCREEN_HEIGHT - y);
}

void Particle::setVelocity(float dx, float dy) {
    this->velocities[0] = dx;
    this->velocities[1] = dy;
}

void Particle::checkCollision() {
    // Check for collision with the bounding box
    float x = this->getXPos();
    float y = this->getYPos();
    if (x - this->circle.getRadius() < LEFT_BOUND) {
        this->setPosition(LEFT_BOUND + this->circle.getRadius() + 1, y);
        this->velocities[0] *= -ELASTICITY;
        this->velocities[1] *= MU_BOUND;
    } else if (x + this->circle.getRadius() > RIGHT_BOUND) {
        this->setPosition(RIGHT_BOUND - this->circle.getRadius() - 1, y);
        this->velocities[0] *= -ELASTICITY;
        this->velocities[1] *= MU_BOUND;
    } else if (y - this->circle.getRadius() < BOTTOM_BOUND) {
        this->setPosition(x, BOTTOM_BOUND + this->circle.getRadius() + 1);
        this->velocities[1] *= -ELASTICITY;
        this->velocities[0] *= MU_BOUND;
    } else if (y + this->circle.getRadius() > TOP_BOUND) {
        this->setPosition(x, TOP_BOUND - this->circle.getRadius() - 1);
        this->velocities[1] *= -ELASTICITY;
        this->velocities[0] *= MU_BOUND;
    }
}

void Particle::updateColor() {
    float velocity = this->getMagnitude();
    if (velocity > MAX_VELOCITY) {
        velocity = MAX_VELOCITY;
    } else if (velocity < MIN_VELOCITY) {
        velocity = MIN_VELOCITY;
    }
    float ratio = (velocity - MIN_VELOCITY) / (MAX_VELOCITY - MIN_VELOCITY);
    int red;
    int green;
    int blue;

    if (ratio < 0.25) {
        red = 0;
        green = 255 - 255 * (1 - ratio / 0.25);
        blue = 255;
    } else if (ratio < 0.5) {
        red = 0;
        green = 255;
        blue = 255 * (1 - (ratio - 0.25) / 0.25);
    } else if (ratio < 0.75) {
        red = 255 - 255 * (1 - (ratio - 0.5) / 0.25);
        green = 255;
        blue = 0;
    } else {
        red = 255;
        green = 255 * (1 - (ratio - 0.75) / 0.25);
        blue = 0;
    }

    this->circle.setFillColor(sf::Color(red, green, blue));
}
