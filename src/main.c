#include "myLib.h"

void mainLoop() { //Loop Simulacion
    while (!WindowShouldClose()){
        BeginDrawing();
            ClearBackground(BLACK);
            for (int i = 0; i < SUB_TICKS; i++){
                simulate();
            }
            drawLines();
            drawParticles();
            DrawFPS(5,5);
        EndDrawing();
    }
    CloseWindow();
}

int main() { 
    int flag;
    //INICIO MENU
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
            "0. Cerrar Programa.\n"
        );

        scanf("%d", &flag);

        switch (flag){
        case 1:
            InitWindow(WIDTH, HEIGHT, "Fis-C-mulator");
            SetTargetFPS(60);
            mainLoop();
            break;
        
        case 2:
            initParticle();
            break;
        
        case 3:
            break;

        case 4:
            initLink();
            break;
            
        case 5:
            printf("Ingresar valor gravedad (Numero Real Positivo, Default 0).\n");
            scanf("%f", &GRAVITY);
            break;
            
        case 6:
            printf("Ingresar coeficiente energia despues de colision ([0, 1], Default: 1).\n");
            scanf("%f", &DAMPER);
            break;
            
        case 7:
            listElements();
            break;
            
        case 0:
            printf("Cerrando programa.\n");
            break;

        default:
            printf("Opcion no existe, intente de nuevo.\n");
            break;
        }
    } while (flag);
    
    //FIN MENU

    return 0;
}