# Tópicos Especiales en Telemática Proyecto 2: Analítica de Texto - HPC

- Douglas Ardila Garcés dardila5@eafit.edu.co
- Andrés Felipe Avendaño aavenda1@eafit.edu.co
- Felipe Macías Herrera fmacias1@eafit.edu.co

## Diseño bajo multihilos con el acercamiento OpenMP

- Documentación [open.md](openmp.md)

## Diseño bajo la metodología PCAM

- Documentación [pcam.md](pcam.md)

## Proceso de compilación y ejecución

    /opt/anaconda3/bin/python procesarArchivos.py
    
    g++ -std=c++11 secuencial.cpp -o secuencial
    time ./secuencial
    
    export OMP_NUM_THREADS=4
    g++ -std=c++11 openmp.cpp -o openmp -fopenmp
    time ./openmp
    
    mpic++ -std=c++11 pcam.cpp -o pcam -fopenmp
    time mpirun -f host.txt -np 3 ./pcam

## Análisis de resultados
- ### Versión serial
- ### Versión paralela
