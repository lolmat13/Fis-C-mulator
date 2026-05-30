# La Mision
## A los alumnos de FIS111 les cuesta visualizar e intuir situaciones y problemas de fisica general mecanica.
El proposito de este proyecto es ayudar a los alumnos de FIS111 a desarrollar una mejor intuicion de los problemas que podrian encontrar en el ramo.\
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

## Que hemos hecho hasta ahora
### - Totalmente implementado:
Tenemos una simulacion basica entre una o varias particulas, las cuales pueden ser expuestas a gravedad o funcionar sin esta, y tienen la capacidad de colisionar entre si mismas y con los bordes de la simulacion, junto con dar la posibilidad de unir estas para generar figuraas sencillas.\
Tambien ya estan implementadas figuras colisionables que funcionan de la misma forma que los bordes de la pantalla, con las particulas pudiendo colisionar correctamente con ellas. Tambien cabe la pena mencionar que no hay un limite de particulas que puedan estar presentes en la simulacion, junto con el hehco de haber transpasado exitosamente el programa de C a C++
### - Mayormente implementado:
Las superficies colisionables estan totalmente desarrolladas, sin embargo, aun estan en desarrollo superficies dinamicas, lo cual quedara para el hito 3. Tambien se esta trabajando la funcion de crear cuerdas, pero todavia no es del todo funcional, funcionando de forma ligeramente erratica
## Que nos falta hacer
Nos falta por rehacer un menu para poder implementar personalmente figuras y superficies, o controlar variables como la gravedad, cosa que se perdio en la transicion de C a C++, por lo que aun se esta rehaciendo
## Instalacion libreria Raylib:
Debido a distintas funciones, graficas y algebraicas que se encuentran presentes en esta libreria, las cuales son ampliamente utiles para el contexto de este proyecto, decidimos implementarla.
- Es importante mencionar que es recomendable realizar la instalacion de los archivos en un quickstart distinto de el ocupado para el hito anterior debido a los archivos que  quedan de residuo en el guardado de este, complicando innecesariamente la descarga y funcionamiento del proyecto. 
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
  Luego de esto:
    - El directorio se descargara como `raylib-quickstart`, y para conveniencia, la renombraremos a `fiscmulator`
    - En este directorio ya se encuentra un directorio `src`, el cual vaciaremos (`cd fiscmulator/src`, `rm *`). 
    - Correr el comando `./premake5 gmake` en la carpeta `build` dentro del directorio `fiscmulator`.

Con estos pasos debiese funcionar la libreria para el proyecto.
## Instalacion de Fiscmulator:
Debido a que el directorio clonado de quickstart de raylib viene con las funciones que ocupamos para nuestro proyecto listas, trabajaremos en el directorio `src` que vaciamos anteriormente, por lo que para la instalacion ahora:

- Agregaremos los archivos de nuestra carpeta `src` (`myLib.cpp`, `myLib.h`) al directorio `src` de fiscmulator.
- Volveremos a la raiz (`fiscmulator`) y correremos `make` (`make` se encarga de la compilacion del proyecto antes de ejecutarlo).
- Luego de esto el programa se puede ejecutar ocupando `./bin/Debug/fiscmulator`.

# Referencias
### - [Teaching myself C so i can build a particle simulation](https://www.youtube.com/watch?v=NorXFOobehY)
### - [Coding a particle simulation in C](https://www.youtube.com/watch?v=7CM0dbib-Jw)
### - [Building collision simulations: An introduction to computer graphics](https://www.youtube.com/watch?v=eED4bSkYCB8)
### - [GitHub libreria RayLib](https://github.com/raysan5/raylib)

