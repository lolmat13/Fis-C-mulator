#include "myLib.h"

float DAMPER = 1;
float SUB_TICKS = 8;
float GRAVITY = 0;
Particle particles[10];
Link links[10];
int particlesAmount = 0;
int linksAmount = 0;

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
void simulate() {
    updateParticles();
    collideParticles(particles, particlesAmount);
    maintainLinkDistance();
}

void updateParticles() {
    for (int i = 0; i < particlesAmount; i++){
        //Cambio de Posicion y aceleracion de gravedad
        Particle *particle = &particles[i];
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
}

void collideParticles(){
    Particle *p1;
    Particle *p2;

    for (int i = 0; i < particlesAmount; i++) {
        p1=&particles[i];
        for (int j = i+1; j < particlesAmount; j++) {
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

void maintainLinkDistance(){
    for (int i = 0; i < linksAmount; i++){
        Vector2 dist = vectorSum(links[i].p2->pos, vectorMult(links[i].p1->pos, -1));
        float absDist = sqrt(pow(dist.x, 2) + pow(dist.y, 2));
        if (absDist != links[i].distance){
            float difference = links[i].distance-absDist;
            dist = vectorNorm(dist);
            links[i].p1->pos = vectorSum(links[i].p1->pos, vectorMult(dist, difference/2));
            links[i].p2->pos = vectorSum(links[i].p2->pos, vectorMult(dist, -difference/2));
        }
    }
}


//Funciones Graficas
void drawParticle(Particle *particle, int i) {
    DrawCircle(particle->pos.x, particle->pos.y, particle->r, WHITE);
    char c[3];
    sprintf(c, "%d", i);
    DrawText(c, particle->pos.x-5, particle->pos.y-10, 20, BLACK);
}

void drawParticles() {
    for (int i = 0; i < particlesAmount; i++) {
        drawParticle(&particles[i], i+1);
    }
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

void initLink(){
    if (particlesAmount < 2) {printf("No hay suficientes particulas para enlazar.\n"); return;}
    int pIndex;
    listParticles();
    printf("Ingrese Particula 1:\n"); scanf("%d", &pIndex); links[linksAmount].p1 = &particles[pIndex-1];
    printf("Ingrese Particula 2:\n"); scanf("%d", &pIndex); links[linksAmount].p2 = &particles[pIndex-1];
    printf("Ingrese Distancia deseada:\n"); scanf("%f", &links[linksAmount].distance);
    linksAmount++;
    return;
}

void listParticles(){
    if (!particlesAmount) {printf("No hay particulas creadas.\n"); return;}
    for (int i = 0; i < particlesAmount; i++){
        printf("Particula %d: Posicion (%.2f, %.2f), Velocidad (%.2f, %.2f), Radio (%.2f), Masa (%.2f)\n", i+1, particles[i].pos.x, particles[i].pos.y, particles[i].dpos.x, particles[i].dpos.y, particles[i].r, particles[i].m);
    }
    return;
}

void listLinks(){
    if (!linksAmount) {printf("No hay links creados.\n"); return;}
    for (int i = 0; i < linksAmount; i++){
        printf("Link %d: Indice Particula A (%d), Indice Particula B (%d), Distancia Deseada (%.2f)\n",
                    i+1, (int)links[i].p1 - (int)&links[0] + 1, (int)links[i].p2 - (int)&links[0] + 1, links[i].distance);
    }
    return;
}

void listElements(){
    listParticles();
    listLinks();
    return;
}