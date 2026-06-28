#include "../include/particle.h"

Particle::Particle(float radius, Vector2 position, Vector2 staringVelocity) {
    this->currentPos = position;
    this->prevPos = {currentPos.x - staringVelocity.x, currentPos.y - staringVelocity.y};
    this->radius = radius;
    this->acceleration = {0, 0};
}

void Particle::update(float dt) {

    Vector2 vel = getVelocity();
    prevPos = currentPos;
    
    // acceleration.y = GRAVITY;

    currentPos.x = currentPos.x + vel.x + acceleration.x * dt * dt;
    currentPos.y = currentPos.y + vel.y + acceleration.y * dt * dt;

    // acceleration = {0.0f, 0.0f};

    if (currentPos.x - radius <= 0) {
        currentPos.x = radius;
        prevPos.x = currentPos.x + vel.x * DAMPING;
    }else if (currentPos.x + radius >= WIDTH) {
        currentPos.x = WIDTH - radius;
        prevPos.x = currentPos.x + vel.x * DAMPING;
    }

    if (currentPos.y - radius <= 0) {
        currentPos.y = radius;
        prevPos.y = currentPos.y + vel.y * DAMPING;
    }else if (currentPos.y + radius >= HEIGHT) {
        currentPos.y = HEIGHT - radius;
        prevPos.y = currentPos.y + vel.y * DAMPING;
    }
}

Vector2 Particle::getVelocity() {
    return (Vector2) {currentPos.x - prevPos.x, currentPos.y - prevPos.y};
}
