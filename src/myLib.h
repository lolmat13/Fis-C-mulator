#include <math.h>
#include <stdio.h>
#include <time.h>
#include "raylib.h"
#define GRAVITY 0
#define WIDTH 1200
#define HEIGHT 800
#define DAMPER 1

typedef struct {
    double x, y, dx, dy, r;
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