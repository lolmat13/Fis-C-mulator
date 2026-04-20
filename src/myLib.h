#include <math.h>
#include <stdio.h>
#include "raylib.h" //No se incluye raymath.h, ya que esta libreraia agrega demasiadas funciones que no seran usadas. Por lo tanto las funciones vectoriales basicas se implementaran independientemente.
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
void drawParticles();
void drawLines();

//Funciones Misc
void initParticle();
void initLink();
void listParticles();
void listLinks();
void listElements();