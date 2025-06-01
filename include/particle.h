#pragma once
#include <raymath.h>

#include "consts.h"

class Particle {
    public:
        Vector2 prevPos;
        Vector2 currentPos;
        Vector2 vel;
        Vector2 acceleration;
        float radius;
        Particle(float radius, Vector2 position, Vector2 startingVelocity);

        void update(float dt);

        Vector2 getVelocity();
};