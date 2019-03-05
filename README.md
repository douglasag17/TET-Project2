# Tópicos Especiales en Telemática Proyecto 2: Analítica de Texto - HPC

- Douglas Ardila Garcés dardila5@eafit.edu.co
- Andrés Felipe Avendaño aavenda1@eafit.edu.co
- Felipe Macías Herrera fmacias1@eafit.edu.co

## Diseño bajo multihilos con el acercamiento OpenMP

- Documentación [open.md](openmp.md)

## Diseño bajo la metodología PCAM

- Documentación [pcam.md](pcam.md)

## Proceso de compilación y ejecución
    g++ -std=c++11 secuencial.cpp -o secuencial
    ./secuencial <word>
    
    g++ -std=c++11 openmp.cpp -o openmp -fopenmp
    ./openmp <word>

## Análisis de resultados
- ### Versión serial
- ### Versión paralela
