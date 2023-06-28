# YimMenu

![Versión en línea](https://img.shields.io/badge/dynamic/json?color=ffab00&label=Versión%20en%20línea&query=%24.game.online&url=https%3A%2F%2Fraw.githubusercontent.com%2FYimMenu%2FYimMenu%2Fmaster%2Fmetadata.json&style=flat-square&labelColor=000000) ![Versión del juego](https://img.shields.io/badge/dynamic/json?color=ffab00&label=Versión%20del%20juego&query=%24.game.build&url=https%3A%2F%2Fraw.githubusercontent.com%2FYimMenu%2FYimMenu%2Fmaster%2Fmetadata.json&style=flat-square&labelColor=000000)

YimMenu es una base de menú de modificaciones para Grand Theft Auto V. Estrictamente con fines educativos.

YimMenu se basa originalmente en [BigBaseV2](https://github.com/Pocakking/BigBaseV2), que fue una base increíble en su momento, pero en la actualidad está un poco desactualizada. Por eso, aquí estoy con un menú actualizado que se centra en proteger al usuario de los modders tóxicos.

## Tabla de contenidos

 * [How to build](#how-to-build)
 * [Make your own flavour of YimMenu](#make-your-own-flavour-of-yimmenu)
 * [Staying Up To Date](#staying-up-to-date)
 * [Project Structure](#project-structure)
 * [Contributing](#contributing)
 
## How to compile YimMenu

Read the [SETUP](https://github.com/YimMenu/YimMenu/wiki/Setup-your-PC-for-YimMenu-Development) guide.

## Make your own flavour of YimMenu

Fork YimMenu and git clone that repository instead of https://github.com/YimMenu/YimMenu.git

Click the below link to make your own fork of YimMenu:
https://github.com/YimMenu/YimMenu/fork
  
## Staying Up To Date

## Mantenerse actualizado

Obtén los últimos cambios de este repositorio.

Con la línea de comandos es tan fácil como:

git pull

CMake debería encargarse automáticamente de los archivos eliminados o agregados sin necesidad de intervención del usuario.

If this is not the case for some reason you'll have to redo the steps in the [Making changes to the source code section of the SETUP](https://github.com/YimMenu/YimMenu/wiki/Setup-your-PC-for-YimMenu-Development#making-changes-to-the-source-code).

Si estás realizando modificaciones personalizadas en el código base y tienes un fork, tendrás que encargarte de mantenerte actualizado con el repositorio principal (este repositorio). Busca información sobre "merge from upstream" y aprende a utilizar Git.

## Estructura del proyecto

- backend/: contiene todas las funciones que se ejecutan en un ciclo, organizadas por categoría.
- gui/: incluye todo lo relacionado con los elementos de la interfaz de usuario.
- hooks/: hooks de funciones.
- native_hooks/: hooks de nativas.
- services/: archivos de servicio para interactuar y mantener cosas.
- util/: funciones de utilidad general para mantener el código lo más compacto y en un solo lugar posible.

## Contributing

Eres libre de contribuir a YimMenu siempre que las características sean útiles, no sean excesivamente tóxicas y no contengan nada relacionado con dinero que pueda hacer que el menú sea objetivo de Take2.

Asegúrate de leer el archivo CONTRIBUTING.md.

