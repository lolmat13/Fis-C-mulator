#include <math.h>
#include <stdio.h>
#include <time.h>
#include "raylib.h"
#define GRAVITY 1
#define WIDTH 900
#define HEIGHT 600

typedef struct {
    float x, y, dx, dy, r;
} Particle;

//Funciones Fisicas
void updateParticle(Particle *particle);
void updateParticles(Particle particles[], int n);
void collisionParticles(Particle particles[], int n);

//Funciones Graficas
void drawParticle(Particle *particle);
void drawParticles(Particle particles[], int n);

//Funciones Misc
int initParticles(Particle particles[]);