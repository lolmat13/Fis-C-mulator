#include "physics.h"

int main() {
    int flag = 1;
    struct Circle c1;
    c1.posX = 100;
    c1.posY = 100;
    c1.speedX = 0;
    c1.speedY = 0;
    while (flag) {
        printf(
            "Circle X position: %.2f\n"
            "Circle Y position: %.2f\n"
            "Circle X speed: %.2f\n"
            "Circle Y speed: %.2f\n",
            c1.posX,
            c1.posY,
            c1.speedX,
            c1.speedY
        );
        physIterate(c1);
        scanf("%d", &flag);
    }

    return 0;
}