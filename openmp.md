# Diseño bajo multihilos con el acercamiento OpenMP

## ¿Qué es OpenMP?
OpenMP es una interfaz de programación de aplicaciones para la programación multiproceso de memoria compartida en múltiples plataformas. Se compone de un conjunto de directivas de compilador, rutinas de biblioteca, y variables de entorno que influyen en el comportamiento del tiempo de ejecución. 

OpenMP se basa en el modelo fork-join, paradigma que proviene de los sistemas Unix, donde una tarea muy pesada se divide en K hilos (fork) con menor peso, para luego "recolectar" sus resultados al final y unirlos en un solo resultado (join).

<imagen>

## Implementación
Bajo esta metodología lo que hicimos fue paralelizar el bloque de código en donde se hace el conteo de cada palabra presente en cada artículo, ya que esta parte del programa es la que más toma tiempo a la hora de ejecutar el programa.
