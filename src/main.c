#include "myLib.h"

Particle particles[];

void mainLoop(Particle particles[], int n) { //Loop Simulacion
    while (!WindowShouldClose()){
        BeginDrawing();
            ClearBackground(BLACK);
            for (int i = 0; i < SUB_TICKS; i++){
                updateParticles(particles, n);
            }
            drawParticles(particles, n);
            DrawFPS(5,5);
        EndDrawing();
    }
}

int main() { 
    InitWindow(WIDTH, HEIGHT, "Fis-C-mulator");
    SetTargetFPS(60);

    //INICIO MENU
    int n = initParticles(particles);
    mainLoop(particles, n);
    //FIN MENU

    CloseWindow();
    return 0;
}