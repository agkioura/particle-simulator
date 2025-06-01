#include <iostream>
#include <raylib.h>
#include <raymath.h>

#define WIDTH 800
#define HEIGHT 600

#include "include/simulation.h"

int main () {
    Simulation s;

    InitWindow(WIDTH, HEIGHT, "Particle Simulator");
    SetTargetFPS(60);

    while (!WindowShouldClose()){
        s.updateParticles(GetFrameTime());
        BeginDrawing();
            ClearBackground(BLACK);
            s.renderParticles();
            DrawFPS(10, 10);
        EndDrawing();
    }

    CloseWindow();
}