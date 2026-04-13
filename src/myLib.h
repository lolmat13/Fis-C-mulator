#include <math.h>
#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include "raylib.h"
#define SUB_TICKS 4
#define GRAVITY 0
#define WIDTH 1200
#define HEIGHT 800
#define DAMPER 1

typedef struct {
    Vector2 pos, dpos;
    float r, m;
} Particle;


//Funciones Fisicas
float dot(Vector2 v, Vector2 u);
Vector2 vectorSum(Vector2 v, Vector2 u);
Vector2 vectorMult(Vector2 v, float n);
void updateParticle(Particle *particle);
void updateParticles(Particle particles[], int n);
void collisionParticles(Particle particles[], int n);

//Funciones Graficas
void drawParticle(Particle *particle, int n);
void drawParticles(Particle particles[], int n);

//Funciones Misc
int initParticles(Particle particles[]);