#pragma once

#include <raylib.h>
#include <raymath.h>

#include "particle.h"
#include "qtree.h"
#include "consts.h"
#include <vector>

class Simulation {
    private:
        std::vector<Particle> particleList;

    public:
        Simulation();
        void updateParticles(float dt, QuadTree &qt);
        void resolveCollisions(Particle &p1, Particle &p2);
        void renderParticles();
        void explode(int mouseX, int mouseY);
};