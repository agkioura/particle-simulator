#include "../include/simulation.h"
#include <iostream>

Simulation::Simulation() {
    int n = PARTICLE_COUNT;

    int offset = WIDTH / (n + 1);
    for (int i = 0; i < n; i++) {
        Particle p(PARTICLE_RADIUS, {(float) offset * (i + 1), HEIGHT / 2}, {0, 0});
        particleList.push_back(p);
    }
}

void Simulation::updateParticles(float dt) {
    for (size_t i = 0; i < particleList.size(); i++) {
        Particle &p1 = particleList[i];
        for (size_t j = i + 1; j < particleList.size(); j++) {
            Particle &other = particleList[j];
            resolveCollisions(p1, other);
        }
        particleList[i].update(dt);
    }
}

void Simulation::resolveCollisions(Particle &p1, Particle &p2) {
    Vector2 collisionAxis = {p1.currentPos.x - p2.currentPos.x, p1.currentPos.y - p2.currentPos.y};
    float distance = Vector2Length(collisionAxis);
    if (distance < PARTICLE_RADIUS * 2) {

        Vector2 n = {collisionAxis.x / distance, collisionAxis.y / distance};
        float overlap = PARTICLE_RADIUS * 2 - distance;

        p1.currentPos.x += 0.5f * overlap * n.x;
        p1.currentPos.y += 0.5f * overlap * n.y;
        p2.currentPos.x -= 0.5f * overlap * n.x;
        p2.currentPos.y -= 0.5f * overlap * n.y;
    }
}

void Simulation::renderParticles() {
    for (auto& p : particleList) {
        DrawCircle(p.currentPos.x, p.currentPos.y, p.radius, WHITE);
    }
}