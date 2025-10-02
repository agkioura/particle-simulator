#pragma once

#include "./box.h"
#include "./particle.h"
#include <vector>
#include <raylib.h>
#include <iostream>

class QuadTree {
    public:
        const int capacity = 4;
        Box boundary;
        std::vector<Particle> particleList;
        bool isDivided;

        QuadTree *nw;
        QuadTree *ne;
        QuadTree *sw;
        QuadTree *se;

        QuadTree();
        QuadTree(Box boundary);
        bool insert(Particle p);
        void subdivide();
        std::vector<Particle> queryRange(Box range);
        void show();
};