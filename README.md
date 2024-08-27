# Biblioteca Sync

**Trabajo universitario para el curso de Principios de Sistemas Operativos, semestre II del 2024**

Este proyecto es desarrollado por Brandon Retana, Ervin Rodriguez, y Kevin Cubillo para el curso de Principios de Sistemas Operativos. El objetivo es implementar y demostrar el uso de un semáforo, una barrera y un Read-Write-Lock desde cero utilizando mutex y las funciones de la biblioteca pthread en C.

## Descripción

El proyecto "Biblioteca Sync" tiene como objetivo principal el aprendizaje académico sobre la implementación y uso de mecanismos de sincronización en sistemas operativos. Las funcionalidades principales incluyen:

- **Semáforo:** Controla el acceso a una sección crítica, permitiendo que solo un número limitado de hilos la ejecute simultáneamente.
- **Barrera:** Sincroniza un conjunto de hilos para que todos alcancen un punto específico de ejecución antes de continuar.
- **Read-Write Lock:** Permite múltiples lectores concurrentes o un único escritor para proteger el acceso a datos compartidos.

Estas implementaciones se han creado desde cero utilizando los mutex y otras funciones de la biblioteca pthread para manejar la sincronización de hilos en un entorno de programación en C.

## Tecnologías y Herramientas

- **Lenguaje de Programación:** C
- **Bibliotecas:** pthread (POSIX threads)
- **Plataforma:** Linux (Fedora)

## Instalación

Para instalar y configurar el proyecto en tu entorno local, sigue los siguientes pasos:

1. **Clonar el repositorio**:
   ```bash
   git clone https://github.com/BrandonRetana/sync-library.git
   ```
2. Moverse la carpeta de scripts
```bash
  cd sync-library/scripts
```
3. Dar permisos de ejecución al archivo init.
```bash
  chmod +x
```
4. Ejecutar el script init.
```bash
./init.sh
```
