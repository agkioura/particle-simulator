#pragma once

#include <raylib.h>
#include <raymath.h>

#include "particle.h"
#include "consts.h"
#include <vector>

class Simulation {
    private:
        std::vector<Particle> particleList;
    
    public:
        Simulation();
        void updateParticles(float dt);
        void resolveCollisions(Particle &p1, Particle &p2);
        void renderParticles();
};