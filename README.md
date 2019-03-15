# Tópicos Especiales en Telemática Proyecto 2: Analítica de Texto - HPC

- Douglas Ardila Garcés dardila5@eafit.edu.co
- Andrés Felipe Avendaño aavenda1@eafit.edu.co
- Felipe Macías Herrera fmacias1@eafit.edu.co

## Diseño bajo multihilos con el acercamiento OpenMP

- Documentación [open.md](openmp.md)

## Diseño bajo la metodología PCAM

- Documentación [pcam.md](pcam.md)

## Proceso de compilación y ejecución en el DCA
### Procesamiento de los datasets
- #### Ejecutar

        /opt/anaconda3/bin/python procesarArchivos.py
### Programa secuencial
- #### Compilar

        g++ -std=c++11 secuencial.cpp -o secuencial
- #### Ejecutar

        time ./secuencial
### Programa paralelo hecho con OpenMP
- #### Asignar número de procesadores a usar

        export OMP_NUM_THREADS=2
- #### Compilar

        g++ -std=c++11 openmp.cpp -o openmp -fopenmp
        
- #### Ejecutar

        time ./openmp
### Programa paralelo hecho con MPI
- #### Compilar

        mpic++ -std=c++11 mpi.cpp -o mpi
- #### Ejecutar

        time mpirun -f host.txt -np 3 ./mpi
### Programa paralelo hecho con OpenMP + MPI
- #### Asignar número de procesadores a usar

        export OMP_NUM_THREADS=2
- #### Compilar

        mpic++ -std=c++11 pcam.cpp -o pcam -fopenmp
- #### Ejecutar

        time mpirun -f host.txt -np 3 ./pcam

## Análisis de resultados
- ### Versión serial
        El tiempo que toma el algoritmo para ejecutar en serial es de 213 segundos en el DCA.
        La siguiente imagen representa un ejemplo de ejecución haciendo búsqueda de trump.
        
- ### Versión paralela
