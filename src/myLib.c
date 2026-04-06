#include "myLib.h"

//Funciones Fisicas
void updateParticle(Particle *particle) {
    //Cambio de Posicion y aceleracion de gravedad
    particle->dy += GRAVITY;
    particle->x += particle->dx;
    particle->y += particle->dy;
    
    double x = particle->x;
    double y = particle->y;
    double r = particle->r;

    //Colisiones con bordes
    if (x - r < 0) {particle->x = r; particle->dx *= -DAMPER;} //borde izquierdo
    if (x + r > WIDTH) {particle->x = WIDTH - r; particle->dx *= -DAMPER;} //borde derecho
    if (y - r < 0) {particle->y = r; particle->dy *= -DAMPER;}  //borde superior
    if (y + r > HEIGHT) {particle->y = HEIGHT - r; particle->dy *= -DAMPER;} //borde inferior    
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

            Vector2 p1Pos = {p1.x, p1.y};
            Vector2 p2Pos = {p2.x, p2.y};
            

            if (CheckCollisionCircles(p1Pos, p1.r, p2Pos, p2.r)) {
                //eliminar overlap
                double distX = p1.x - p2.x;
                double distY = p1.y - p2.y;
                double absD = sqrt(pow(distX, 2) + pow(distY, 2));
                double normX = distX / absD;
                double normY = distY / absD;
                double overlap = p2.r + p1.r - absD;
                
                particles[i].x += normX * overlap / 2;
                particles[i].y += normY * overlap / 2;
                particles[j].x += -normX * overlap / 2;
                particles[j].y += -normY * overlap / 2;

                //cambio de direcicon vector velocidad
                double tanX = -normY;
                double tanY = normX;

                particles[i].dx = DAMPER*(p1.dx * tanX + p1.dy * tanY);
                particles[i].dy = DAMPER*(p2.dx * normX + p2.dy * normY);
                particles[j].dx = DAMPER*(p2.dx * tanX + p2.dy * tanY);
                particles[j].dy = DAMPER*(p1.dx * normX + p1.dy * normY);

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
    int n = GetRandomValue(10, 10);

    for (int i = 0; i < n; i++) {
        particles[i].x = GetRandomValue(100, HEIGHT - 100);
        particles[i].y = GetRandomValue(100, WIDTH - 100);
        particles[i].dx = GetRandomValue(-5, 5);
        particles[i].dy = GetRandomValue(-5, 5);
        particles[i].r = GetRandomValue(10, 10);
    }
    return n;
}