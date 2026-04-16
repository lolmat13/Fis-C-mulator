#include <math.h>
#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include "raylib.h"
#define WIDTH 1200
#define HEIGHT 800
#define ARRAY_SIZE(array) (sizeof(array)/sizeof(array[0]))
extern float DAMPER;
extern float SUB_TICKS;
extern float GRAVITY;

//Objetos Fisicos
typedef struct {
    Vector2 pos, dpos;
    float r, m;
} Particle;

extern Particle particles[];
extern int particlesAmount;

typedef struct {
    Particle *p1, *p2;
    float distance;
} Link;

//Funciones Vectoriales
float dot(Vector2 v, Vector2 u);
Vector2 vectorSum(Vector2 v, Vector2 u);
Vector2 vectorMult(Vector2 v, float n);
Vector2 vectorNorm(Vector2 v);

//Funciones Fisicas
void updateParticles();
void simulate();
void collideParticles();
void maintainLinkDistance();

//Funciones Graficas
void drawParticle(Particle *particle, int i);
void drawParticles();
void drawLine();

//Funciones Misc
void initParticle();
void initLink();
void listParticles();
void listLinks();
void listElements();