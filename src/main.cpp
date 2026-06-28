#include <iostream>
#include <vector>
#include <string.h>
#include <cstdlib>
#include <raylib.h>
#include <raymath.h>

#include "../include/simulation.h"
#include "../include/box.h"
#include "../include/qtree.h"

int main () {
    Simulation s;
    
    InitWindow(WIDTH, HEIGHT, "Particle Simulator");
    SetTargetFPS(60);
    
    std::string pointCount = "Point count: " + std::to_string(PARTICLE_COUNT);
    while (!WindowShouldClose()){
        QuadTree qt;
        if (IsMouseButtonPressed(0)) {
            s.explode(GetMouseX(), GetMouseY());
        }

        BeginDrawing();
        ClearBackground(BLACK);
            s.updateParticles(GetFrameTime(), qt);
            s.renderParticles();
            // qt.show(); 
            DrawFPS(10, 10);
            DrawText(pointCount.c_str(), 100, 10, 16, GREEN);
        EndDrawing();
    }

    CloseWindow();
}
