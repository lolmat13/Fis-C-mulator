#include "physics.h"

Particle particles[];

void mainLoop(Particle particles[], int n) {
    while (!WindowShouldClose()){
        BeginDrawing();
            ClearBackground(BLACK);
            updateParticles(particles, n);
            collisionParticles(particles, n);
            drawParticles(particles, n);
            DrawFPS(5,5);
        EndDrawing();
    }
}

int main() { 
    InitWindow(WIDTH, HEIGHT, "Fis-C-mulator");
    SetTargetFPS(60);

    int n = initParticles(particles);
    mainLoop(particles, n);

    CloseWindow();
    
    return 0;
}