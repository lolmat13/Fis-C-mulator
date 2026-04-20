#include "myLib.h"

float DAMPER = 1;
float SUB_TICKS = 8;
float GRAVITY = 0;
Particle particles[10];
Link links[10];
int particlesAmount = 0;
int linksAmount = 0;

//Funciones Fisicas
void simulate() {
    updateParticles();
    collideParticles(particles, particlesAmount);
    maintainLinkDistance();
}

void updateParticles() {
    for (int i = 0; i < particlesAmount; i++) {
        //Cambio de Posicion y aceleracion de gravedad
        Particle *particle = &particles[i];
        particle->dpos.y += GRAVITY / SUB_TICKS;
        particle->pos = Vector2Add(particle->pos, Vector2Scale(particle->dpos, 1 / SUB_TICKS));
        
        float x = particle->pos.x;
        float y = particle->pos.y;
        float r = particle->r;

        //Colisiones con bordes
        if (x - r < 0) {particle->pos.x = r; particle->dpos.x *= -DAMPER;} //borde izquierdo
        if (x + r > WIDTH) {particle->pos.x = WIDTH - r; particle->dpos.x *= -DAMPER;} //borde derecho
        if (y - r < 0) {particle->pos.y = r; particle->dpos.y *= -DAMPER;}  //borde superior
        if (y + r > HEIGHT) {particle->pos.y = HEIGHT - r; particle->dpos.y *= -DAMPER;} //borde inferior    
    }
}

void collideParticles() {
    Particle *p1;
    Particle *p2;

    for (int i = 0; i < particlesAmount; i++) {
        p1=&particles[i];
        for (int j = i+1; j < particlesAmount; j++) {
            p2=&particles[j];
            if (CheckCollisionCircles(p1->pos, p1->r, p2->pos, p2->r)) {
                //eliminar overlap
                Vector2 dist = Vector2Subtract(p1->pos, p2->pos); //vector desde p2 a p1
                float absD = Vector2Length(dist); //magnitud de ese vector
                Vector2 normD = Vector2Normalize(dist);  //vector p2->p1 normalizado
                float overlap = p1->r + p2->r - absD;
                p1->pos = Vector2Add(p1->pos, Vector2Scale(normD, overlap / 2));
                p2->pos = Vector2Subtract(p2->pos, Vector2Scale(normD, overlap / 2));

                //cambio de direcicon vector velocidad  
                p1->dpos = Vector2Reflect(p1->dpos, normD);
                p2->dpos = Vector2Reflect(p2->dpos, normD);
            }
        }
    }
}

void maintainLinkDistance() {
    for (int i = 0; i < linksAmount; i++) {
        Vector2 p1pos = links[i].p1->pos;
        Vector2 p2pos = links[i].p2->pos;
        Vector2 dist = Vector2Subtract(p2pos, p1pos);
        float dif = links[i].distance - Vector2Length(dist);
        if (fabs(dif) > 0.01) {
            links[i].p1->pos = Vector2Subtract(p1pos, Vector2Scale(Vector2Normalize(dist), dif/2));
            links[i].p2->pos = Vector2Add(p2pos, Vector2Scale(Vector2Normalize(dist), dif/2));
        }
    }
}


//Funciones Graficas
void drawParticles() {
    for (int i = 0; i < particlesAmount; i++) {
        DrawCircle(particles[i].pos.x, particles[i].pos.y, particles[i].r, WHITE);
    }
}

void drawLines() {
    for (int i = 0; i < linksAmount; i++) {
        DrawLineEx(links[i].p1->pos, links[i].p2->pos, 5, WHITE);
    }
}

void drawFrame() {
    drawParticles();
    drawLines();
}

//Funciones Misc
void initParticle() {
    printf("Ingrese posicion inicial X (Numero Real):\n"); scanf("%f", &particles[particlesAmount].pos.x);
    printf("Ingrese posicion inicial Y (Numero Real):\n"); scanf("%f", &particles[particlesAmount].pos.y);
    printf("Ingrese velocidad inicial X (Numero Real):\n"); scanf("%f", &particles[particlesAmount].dpos.x);
    printf("Ingrese velocidad inicial Y (Numero Real):\n"); scanf("%f", &particles[particlesAmount].dpos.y);
    printf("Ingrese radio (Numero Real):\n"); scanf("%f", &particles[particlesAmount].r); 
    printf("Ingrese masa (Numero Real):\n"); scanf("%f", &particles[particlesAmount].m);
    particlesAmount++;
    return;
}

void initLink() {
    if (particlesAmount < 2) {printf("No hay suficientes particulas para enlazar.\n"); return;}
    int pIndex;
    listParticles();
    printf("Ingrese Particula 1:\n"); scanf("%d", &pIndex); links[linksAmount].p1 = &particles[pIndex-1];
    printf("Ingrese Particula 2:\n"); scanf("%d", &pIndex); links[linksAmount].p2 = &particles[pIndex-1];
    printf("Ingrese Distancia deseada:\n"); scanf("%f", &links[linksAmount].distance);
    linksAmount++;
    return;
}

void listParticles() {
    if (!particlesAmount) {printf("No hay particulas creadas.\n"); return;}
    for (int i = 0; i < particlesAmount; i++) {
        printf("Particula %d: Posicion (%.2f, %.2f), Velocidad (%.2f, %.2f), Radio (%.2f), Masa (%.2f)\n", i+1, particles[i].pos.x, particles[i].pos.y, particles[i].dpos.x, particles[i].dpos.y, particles[i].r, particles[i].m);
    }
    return;
}

void listLinks() {
    if (!linksAmount) {printf("No hay links creados.\n"); return;}
    for (int i = 0; i < linksAmount; i++) {
        printf("Link %d: Indice Particula A (%ld), Indice Particula B (%ld), Distancia Deseada (%.2f)\n",
                    i+1, (links[i].p1 - &particles[0]) + 1, (links[i].p2 - &particles[0]) + 1, links[i].distance);
    }
    return;
}

void listElements() {
    listParticles();
    listLinks();
    return;
}