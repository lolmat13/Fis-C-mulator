#include "myLib.h"

void mainLoop() { //Loop Simulacion
    InitWindow(WIDTH, HEIGHT, "Fis-C-mulator");
    SetTargetFPS(60);
    while (!WindowShouldClose()){
        BeginDrawing();
            ClearBackground(BLACK);
            for (int i = 0; i < SUB_TICKS; i++){
                simulate();
            }
            drawFrame();
            DrawFPS(5,5);
        EndDrawing();
    }
    CloseWindow();
}

int main() { 
    int flag;
    do
    {
        printf(
            "Escoger Opcion:\n"
            "1. Iniciar Simulacion.\n"
            "2. Crear Particula.\n"
            "3. Crear Superficie.\n"
            "4. Crear Superficie Dinamica\n"
            "5. Configurar Gravedad.\n"
            "6. Configurar Perdida de energia.\n"
            "7. Listar Elementos.\n"
            "8. Eliminar Todos los Elementos.\n"
            "0. Cerrar Programa.\n"
        );

        scanf("%d", &flag);

        switch (flag){
        case 1:
            mainLoop();
            break;
        
        case 2:
            initParticle();
            break;
        
        case 3:
            printf("Funcion no implementada.\n");
            break;

        case 4:
            printf("Esta funcion esta implementada, pero la fisica de particulas conectadas no esta completa.\n");
            initLink();
            break;
            
        case 5:
            gravity: 
            printf("Ingresar valor gravedad ([Real], Default 0).\n");
            if(!scanf("%f", &GRAVITY)){
                printf("Input Invalido.\n");
                goto gravity;
            }
            break;
            
        case 6:
            damper: 
            printf("Ingresar coeficiente energia despues de colision ([0, 1], Default: 1).\n");
            if(!scanf("%f", &DAMPER)){
                printf("Input Invalido.\n");
                goto damper;
            }
            break;
            
        case 7:
            listElements();
            break;
            
        case 8:
            clearAll();
            break;

        case 0:
            printf("Cerrando programa.\n");
            break;

        default:
            printf("Opcion no existe, intente de nuevo.\n");
            break;
        }
    } while (flag);

    return 0;
}