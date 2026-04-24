#include <math.h>
#include <stdio.h>
#include "raylib.h"
#include "raymath.h"

#define WIDTH 800
#define HEIGHT 800

extern float DAMPER;
extern float SUB_TICKS;
extern float GRAVITY;

//Objetos Fisicos
typedef struct {
    Vector2 pos, dpos;
    float r, m;
} Particle;

typedef struct {
    Particle *p1, *p2;
    float distance;
} Link;

//Funciones Fisicas
void updateParticles();
void simulate();
void resolveCollision();
void collideParticles();
void maintainLinkDistance();

//Funciones Graficas
void drawParticles();
void drawLines();
void drawFrame();

//Funciones Misc
void clearAll();
void initParticle();
void initLink();
void listParticles();
void listLinks();
void listElements();