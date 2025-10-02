#include "../include/simulation.h"
#include <iostream>

Simulation::Simulation() {
    int n = PARTICLE_COUNT;
    int maxCol = 10;
    int offsetX = (WIDTH / 2) - (PARTICLE_RADIUS * 2 * maxCol) / 2;
    int offsetY = (HEIGHT / 2) - (PARTICLE_RADIUS * 2 * maxCol) / 2;

    int row = 0;
    int col = 0;
    for (int i = 0; i < n; i++) {
        Particle p(PARTICLE_RADIUS, 
            {
                (float) ((col * PARTICLE_RADIUS * 2 + PARTICLE_RADIUS) + offsetX), 
                (float) ((row * PARTICLE_RADIUS * 2 + PARTICLE_RADIUS) + offsetY)
            }, {0.0f, 0.0f});
        particleList.push_back(p);
        
        col++;
        if (col >= maxCol) {
            col = 0;
            row++;
        }
    }
}

void Simulation::updateParticles(float dt, QuadTree &qt) {
    for (size_t i = 0; i < particleList.size(); i++) {
        Particle &p1 = particleList[i];
        qt.insert(p1);
        // for (size_t j = i + 1; j < particleList.size(); j++) {
        //     Particle &other = particleList[j];
        //     if (p1.currentPos != other.currentPos) 
        //     resolveCollisions(p1, other);
        // }
        // particleList[i].update(dt);
    }
    for (size_t i = 0; i < particleList.size(); i++) {
        Particle &p1 = particleList[i];
        std::vector<Particle> particles = qt.queryRange((Box){p1.currentPos.x, p1.currentPos.y, p1.radius});
        for (size_t j = 0; j < particles.size(); j++) {
            Particle &other = particles[j];
            if (p1.currentPos != other.currentPos) 
            resolveCollisions(p1, other);
        }
        p1.update(dt);
    }
}

void Simulation::explode(int mouseX, int mouseY) {
    int explodeRadius = 100;
    Vector2 mousePos = {(float) mouseX, (float) mouseY};
    for (size_t i = 0; i < particleList.size(); i++) {
        Particle &p1 = particleList[i];
        Vector2 collisionAxis = {p1.currentPos.x - mousePos.x, p1.currentPos.y - mousePos.y};
        float distance = Vector2Length(collisionAxis);
        if (distance < explodeRadius) {
            Vector2 n = {collisionAxis.x / distance, collisionAxis.y / distance};
            float overlap = PARTICLE_RADIUS * 2 - distance;

            p1.currentPos.x += 0.5f * overlap * n.x;
            p1.currentPos.y += 0.5f * overlap * n.y;
        }
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