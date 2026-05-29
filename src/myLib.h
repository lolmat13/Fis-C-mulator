#include <math.h>
#include <stdio.h>
#include <vector>
#include "raylib.h"
#include "raymath.h"

#define WIDTH 800
#define HEIGHT 800

extern double dt;
extern double DAMPER;
extern int SUB_TICKS;


class VerletParticle {
private:
    Vector2 pos, posPrev, accel;
    double r, m;
    bool dynamic;

public:
    VerletParticle(Vector2 current, double radius, bool dyn);
    ~VerletParticle();

    Vector2 getCurrentPosition();
    Vector2 getPreviousPosition();
    Vector2 getAcceleration();
    Vector2 getVelocity();
    double getRadius();
    double getMass();
    bool isDynamic();
    
    void setPosition(Vector2 posCurrent);
    void setVelocity(Vector2 vel);
    void setMass(double mass);
    void setAcceleration(Vector2 acceleration);
    void applyForce(Vector2 force);

    void updatePos();
    void constrain();
    void constrainDistance(Vector2 anchor, double distance);
};

typedef struct Link {
    size_t a, b;
    double distance;
} Link;