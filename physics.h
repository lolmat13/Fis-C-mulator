#include <stdio.h>

#define GRAVITY 1

struct Circle {
    float posX;
    float posY;
    float speedX;
    float speedY;
    float r;
    float mass;
};

void physIterate(struct Circle body);