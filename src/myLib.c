#include "myLib.h"

//Funciones Fisicas
void updateParticle(Particle *particle) {
    //Cambio de Posicion y aceleracion de gravedad
    particle->x += particle->dx;
    particle->y += particle->dy;
    //particle->dy += GRAVITY;
    
    float x = particle->x;
    float y = particle->y;
    float r = particle->r;

    //Colisiones con bordes
    if (x - r < 0) {particle->x = r; particle->dx *= -1;} //borde izquierdo
    if (x + r > WIDTH) {particle->x = WIDTH - r; particle->dx *= -1;} //borde derecho
    if (y - r < 0) {particle->y = r; particle->dy *= -1;}  //borde superior
    if (y + r > HEIGHT) {particle->y = HEIGHT - r; particle->dy *= -1;} //borde inferior    
}

void updateParticles(Particle particles[], int n) {
    for (int i = 0; i < n; i++) {
        updateParticle(&particles[i]);
    }
}

void collisionParticles(Particle particles[], int n){
    Particle p1;
    Particle p2;

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (i==j) break; //No colisionar particula con si misma

            p1=particles[i];
            p2=particles[j];

            float d = sqrt(pow(p1.x - p2.x, 2) + pow(p1.y - p2.y, 2));

            if ( d <= p1.r + p2.r) {
                printf("particles collided!\n");
                float normX = (p1.x - p2.x) / d;
                float normY = (p1.y - p2.y) / d;
                float overlap = d - (p2.r - p1.r);
                p1.x += normX * overlap;
                p1.y += normY * overlap;
            }
        }
    }
}

//Funciones Graficas
void drawParticle(Particle *particle) {
    DrawCircle(particle->x, particle->y, particle->r, WHITE);
}

void drawParticles(Particle particles[], int n) {
    for (int i = 0; i < n; i++) {
        drawParticle(&particles[i]);
    }
}

//Funciones Misc
int initParticles(Particle particles[]) {
    SetRandomSeed(time(NULL));
    int n = GetRandomValue(5, 20);

    for (int i = 0; i < n; i++) {
        particles[i].x = GetRandomValue(100,500);
        particles[i].y = GetRandomValue(100,800);
        particles[i].dx = GetRandomValue(-15, 15);
        particles[i].dy = GetRandomValue(-15, 15);
        particles[i].r = GetRandomValue(10, 30);
    }
    return n;
}