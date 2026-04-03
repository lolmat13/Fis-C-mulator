#include "physics.h"

void physIterate(struct Circle body) {
    body.posX += body.speedX;
    body.posY += body.speedY;
    body.speedY -= GRAVITY;
    return;
}