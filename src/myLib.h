#include <math.h>
#include <stdio.h>
#include <vector>
#include "raylib.h"
#include "raymath.h"

#define WIDTH 1200
#define HEIGHT 800

extern float dt;
extern float DAMPER;
extern int SUB_TICKS;


class VerletParticle {
private:
    Vector2 pos, posPrev, accel;
    float r, m;

public:
    VerletParticle(Vector2 current, float radius);
    ~VerletParticle();

    Vector2 getCurrentPosition();
    Vector2 getPreviousPosition();
    Vector2 getAcceleration();
    Vector2 getVelocity();
    float getRadius();
    float getMass();
    
    void setVelocity(Vector2 vel);
    void setMass(float mass);
    void applyForce(Vector2 force);

    void updatePos();
    void constrain();
    void constrainDistance(Vector2 anchor, float distance);
    void step();
};

typedef struct Link {
    size_t a, b;
    float distance;
} Link;