#include "myLib.h"

//Funciones Vectoriales
float dot(Vector2 v, Vector2 u){
    return v.x * u.x + v.y * u.y;
}

Vector2 vectorSum(Vector2 v, Vector2 u){
    Vector2 sum = {v.x + u.x, v.y + u.y};
    return sum;
}

Vector2 vectorMult(Vector2 v, float n){
    Vector2 scaled = {v.x * n, v.y * n};
    return scaled;
}

Vector2 vectorNorm(Vector2 v){
    Vector2 normD = vectorMult(v, (dot(v, v)));
    return normD;
}

//Funciones Fisicas
void updateParticle(Particle *particle) {
    //Cambio de Posicion y aceleracion de gravedad
    particle->dpos.y += GRAVITY / SUB_TICKS;
    particle->pos = vectorSum(particle->pos, vectorMult(particle->dpos, 1 / SUB_TICKS));
    
    float x = particle->pos.x;
    float y = particle->pos.y;
    float r = particle->r;

    //Colisiones con bordes
    if (x - r < 0) {particle->pos.x = r; particle->dpos.x *= -DAMPER;} //borde izquierdo
    if (x + r > WIDTH) {particle->pos.x = WIDTH - r; particle->dpos.x *= -DAMPER;} //borde derecho
    if (y - r < 0) {particle->pos.y = r; particle->dpos.y *= -DAMPER;}  //borde superior
    if (y + r > HEIGHT) {particle->pos.y = HEIGHT - r; particle->dpos.y *= -DAMPER;} //borde inferior    
}

void updateParticles(Particle particles[], int n) {
    for (int i = 0; i < n; i++) {
        updateParticle(&particles[i]);
    }
    collisionParticles(particles, n);
}

void collisionParticles(Particle particles[], int n){
    Particle *p1;
    Particle *p2;

    for (int i = 0; i < n; i++) {
        p1=&particles[i];
        for (int j = i+1; j < n; j++) {
            p2=&particles[j];

            if (CheckCollisionCircles(p1->pos, p1->r, p2->pos, p2->r)) {
                //eliminar overlap
                Vector2 dist = vectorSum(p1->pos, vectorMult(p2->pos, -1)); //vector desde p2 a p1
                float absD = sqrt(dot(dist, dist)); //magnitud de ese vector
                Vector2 normD = vectorMult(dist, 1/absD);  //vector p2->p1 normalizado
                float overlap = p1->r + p2->r - absD;
                
                p1->pos = vectorSum(p1->pos, vectorMult(normD, overlap / 2));
                p2->pos = vectorSum(p2->pos, vectorMult(normD, -overlap / 2));

                //cambio de direcicon vector velocidad  
                Vector2 temp1 = p1->dpos;
                Vector2 temp2 = p2->dpos;
                Vector2 tanD = {-normD.y, normD.x};
                Vector2 dpos1n = vectorMult(normD, dot(temp1, normD) / dot(normD, normD)); 
                Vector2 dpos1t = vectorMult(tanD, dot(temp1, tanD) / dot(tanD, tanD));
                Vector2 dpos2n = vectorMult(normD, dot(temp2, normD) / dot(normD, normD));
                Vector2 dpos2t = vectorMult(tanD, dot(temp2, tanD) / dot(tanD, tanD));

                p1->dpos = vectorMult(vectorSum(dpos2n, dpos1t), DAMPER);
                p2->dpos = vectorMult(vectorSum(dpos1n, dpos2t), DAMPER);

                
            }
        }
    }
}

//Funciones Graficas
void drawParticle(Particle *particle, int n) {
    DrawCircle(particle->pos.x, particle->pos.y, particle->r, WHITE);
    char c[3];
    sprintf(c, "%d", n);
    DrawText(c, particle->pos.x-5, particle->pos.y-10, 20, BLACK);
}

void drawParticles(Particle particles[], int n) {
    for (int i = 0; i < n; i++) {
        drawParticle(&particles[i], i+1);
    }
}

//Funciones Misc
int initParticles(Particle particles[]) {
    SetRandomSeed(time(NULL));
    int n = GetRandomValue(100, 100);

    for (int i = 0; i < n; i++) {
        particles[i].pos.x = GetRandomValue(100, WIDTH - 100);
        particles[i].pos.y = GetRandomValue(100, HEIGHT - 100);
        particles[i].dpos.x = GetRandomValue(-5, 5) / SUB_TICKS;
        particles[i].dpos.y = GetRandomValue(-5, 5) / SUB_TICKS;
        particles[i].r = GetRandomValue(20, 20);
        particles[i].m = particles[i].r;
    }
    return n;
}