# YimMenu

![Versión en línea](https://img.shields.io/badge/dynamic/json?color=ffab00&label=Versión%20en%20línea&query=%24.game.online&url=https%3A%2F%2Fraw.githubusercontent.com%2FYimMenu%2FYimMenu%2Fmaster%2Fmetadata.json&style=flat-square&labelColor=000000) ![Versión del juego](https://img.shields.io/badge/dynamic/json?color=ffab00&label=Versión%20del%20juego&query=%24.game.build&url=https%3A%2F%2Fraw.githubusercontent.com%2FYimMenu%2FYimMenu%2Fmaster%2Fmetadata.json&style=flat-square&labelColor=000000)

YimMenu es una base de menú de modificaciones para Grand Theft Auto V. Estrictamente con fines educativos.

YimMenu se basa originalmente en [BigBaseV2](https://github.com/Pocakking/BigBaseV2), que fue una base increíble en su momento, pero en la actualidad está un poco desactualizada. Por eso, aquí estoy con un menú actualizado que se centra en proteger al usuario de los modders tóxicos.

## Tabla de contenidos

- [Cómo compilar](#cómo-compilar)
  - [Curl](#curl)
  - [Git](#git)
  - [CMake](#cmake)
  - [Clonar y generar archivos del proyecto](#clonar-y-generar-archivos-del-proyecto)
- [Mantenerse actualizado](#mantenerse-actualizado)
- [Estructura del proyecto](#estructura-del-proyecto)
- [Funcionalidades](#funcionalidades)
- [Contribución](#contribución)

## Cómo compilar

Requisitos:

- [Git](#git)
- [CMake](#cmake)

Si tienes ambos requisitos mencionados anteriormente, puedes saltar a [clonar el repositorio de Git y generar los archivos del proyecto](#clonar-y-generar-archivos-del-proyecto).

### Curl

Curl debería estar instalado en tu computadora, pero si tienes problemas para compilar el proyecto, necesitarás descargar e instalar curl.

[Enlace de descarga](https://curl.se/download.html)

### Git

Si no has instalado Git en tu sistema, debes hacerlo, ya que es **REQUERIDO** para configurar un entorno de compilación funcional.

[Enlace de descarga](https://git-scm.com/download/win)

### CMake

CMake se utiliza para generar los archivos del proyecto. Si nunca lo has utilizado antes, deberás descargar e instalarlo.

[Enlace de descarga](https://cmake.org/download/)

### Clonar y generar archivos del proyecto

- Asegúrate de haber instalado Git y CMake.

- Clona el repositorio:
  git clone https://github.com/YimMenu/YimMenu.git

- Ingresa al directorio que acabas de clonar:
  cd YimMenu

#### Generar archivos del proyecto

> **Nota**
> Si agregas o quitas archivos, deberás ejecutar los siguientes comandos nuevamente o recibirás un error al compilar.

- Solo para Windows

  - Visual Studio

    Si solo utilizas Visual Studio y no deseas lidiar con la línea de comandos, Visual Studio tiene una extensión de CMake que hace todo el trabajo.

    Asegúrate de tenerla instalada. [Puedes descargarla aquí](https://learn.microsoft.com/en-us/cpp/build/cmake-projects-in-visual-studio?view=msvc-170#installation).

    Luego, simplemente abre Visual Studio, abre una carpeta local y selecciona la carpeta YimMenu que se creó con el comando git clone.

    Deja que la extensión de CMake genere los archivos necesarios para compilar. Puedes seguir el progreso en la pestaña de salida de Visual Studio.

    Luego, simplemente compila utilizando el menú Build en la parte superior y haz clic en Build All.

- Otros sistemas operativos / IDEs

  Si utilizas otro sistema operativo o prefieres utilizar la consola en Windows, simplemente sigue estos pasos:

  mkdir build
  cd build
  cmake ..

  Ahora podrás abrir la solución y compilarla.

## Mantenerse actualizado

Obtén los últimos cambios de este repositorio.

Con la línea de comandos es tan fácil como:

git pull

CMake debería encargarse automáticamente de los archivos eliminados o agregados sin necesidad de intervención del usuario.

Si por alguna razón eso no sucede, deberás repetir los pasos en la sección Generar archivos del proyecto mencionada anteriormente.

Si estás realizando modificaciones personalizadas en el código base y tienes un fork, tendrás que encargarte de mantenerte actualizado con el repositorio principal (este repositorio). Busca información sobre "merge from upstream" y aprende a utilizar Git.

## Estructura del proyecto

- backend/: contiene todas las funciones que se ejecutan en un ciclo, organizadas por categoría.
- gui/: incluye todo lo relacionado con los elementos de la interfaz de usuario.
- hooks/: hooks de funciones.
- native_hooks/: hooks de nativas.
- services/: archivos de servicio para interactuar y mantener cosas.
- util/: funciones de utilidad general para mantener el código lo más compacto y en un solo lugar posible.

## Funcionalidades

A continuación se muestra una lista incompleta de características que considero destacadas de esta "base" o menú.

- Engaño de retorno de nativas.
- Configuraciones personalizadas settings con comparación profunda si se han realizado cambios, incluido el guardado automático.
- Código fuente claro y bien estructurado.
- Incluye un grupo de subprocesos para encolar tareas que no deben bloquear el subproceso del juego, muy similar a un grupo de hilos.
- Archivo natives.hpp actualizado de https://nativedb.spyral.dev.
- Estructuras implementadas de ReClass.NET, accesibles desde una variable global llamada g_local_player definida en common.hpp.

## Contribución

Eres libre de contribuir a YimMenu siempre que las características sean útiles, no sean excesivamente tóxicas y no contengan nada relacionado con dinero que pueda hacer que el menú sea objetivo de Take2.

Asegúrate de leer el archivo CONTRIBUTING.md.

