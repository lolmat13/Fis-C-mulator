# La Mision
## A los alumnos de FIS111 les cuesta visualizar e intuir situaciones y problemas de fisica general mecanica.
El proposito de este proyecto es ayudar a los alumnos de FIS111 a desarrollar una mejor intuicion de los problemas que prodrian encontrar en el ramo.\
Este programa les servira para poder jugar con distintas situaciones fisicas, y asi lograr internalizar la intuicion y sentido comun para guiarlos en una direccion general de soluciones al momento de realizar evaluaciones.

# El Equipo
Franco Cardenas\
Claudio Moya\
Martín Muñoz\
Sebastian Villalobos

# El Proyecto
El proyecto, como mencionamos anteriormente, apunta a visualizar problemas que podrian ser visibles en el ramo de FIS-111, lo que incluiria:
- Gravedad que afecte a los objetos presentes
- Colisiones entre particulas
- Objetos dinamicos
- Superficies colisionables
- Roce
- Poleas
- Resortes

Por ahora, planeamos tener listas las funciones de gravedad, particulas, y superficies colisionables, trabajando en el resto mientras avance el tiempo.
## Que hemos hecho hasta ahora
### - Totalmente implementado:
Tenemos una simulacion basica entre una o varias particulas, las cuales pueden ser expuestas a gravedad o funcionar sin esta, y tienen la capacidad de colisionar entre si mismas y con los bordes de la simulacion.
### - Mayormente implementado:
Esta ya en progreso la funcion de unir varias particulas entre ellas, cumpliendo todas las mismas funciones de particulas individuales.
## Que nos falta hacer
Debido a que para este primer hito quisimos mantener nuestro enfoque en solo lo escencial para asegurar que el simulador funcione correctamente, incluyendo en esas funcionalidades la visualizacion grafica de el proyecto y colisiones basicas, funciones como el roce o poleas se dejaran para hitos posteriores en el progreso del proyecto.
## Instalacion libreria Raylib:
Debido a distintas funciones, graficas y algebraicas que se encuentran presentes en esta libreria, las cuales son ampliamente utiles para el contexto de este proyecto, decidimos implementarla.
### - Descarga en GNU Linux:
La libreria tiene varias dependencias cruciales para su funcionamiento, por lo que primero revisaremos las herramientas necesarias.
- **Herramientas*:
  Un compilador GCC, make y git
  - sudo apt install build-essential git
- **Librerias**:
   Las lbrerias requeridas serian **ALSA**, para audio, **MESA** para graficos acelerados, y **X11**, para la aplicacion como ventana.
  - **Ubuntu**: `sudo apt install libasound2-dev libx11-dev libxrandr-dev libxi-dev libgl1-mesa-dev libglu1-mesa-dev libxcursor-dev libxinerama-dev libwayland-dev libxkbcommon-dev`
  - **Fedora**: `sudo dnf install alsa-lib-devel mesa-libGL-devel libX11-devel libXrandr-devel libXi-devel libXcursor-devel libXinerama-devel libatomic`
  - **Bash**: `sudo apt update`\
    `sudo apt install build-essential git make libasound2-dev mesa-common-dev libx11-dev libxrandr-dev libxi-dev xorg-dev libgl1-mesa-dev libglu1-mesa-dev`
- **Raylib**: Para la instalacion de la libreria en si, podemos copiarla directamente desde git por medio de:
  - `https://github.com/raylib-extras/raylib-quickstart.git`
  - `git clone https://github.com/raylib-extras/raylib-quickstart.git`\
  Luego de esto, podemos incluirla al proyecto por medio de:
    - Asegurar que ambos el archivo de proyecto y la bibloteca copiada de git esten un un mismo entorno
    - Correr el comando `./premake5 gmake`
    - Volver a la carpeta raiz
    - Correr `make`\
Con estos pasos debiese funcionar la libreria para el proyecto.
# Referencias
### - [Teaching myself C so i can build a particle simulation](https://www.youtube.com/watch?v=NorXFOobehY)
### - [Coding a particle simulation in C](https://www.youtube.com/watch?v=7CM0dbib-Jw)
### - [Building collision simulations: An introduction to computer graphics](https://www.youtube.com/watch?v=eED4bSkYCB8)
### - [GitHub libreria RayLib](https://github.com/raysan5/raylib)

