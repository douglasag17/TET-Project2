#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include <map>
#include <iterator>
#include <ctype.h> //toupper y tolower
#include <stdio.h>
#include <string.h>
#include "mpi.h"
#include <omp.h>

using namespace std;

int main (int argc, char *argv[]) {
    MPI_Init (&argc, &argv); // Initialize MPI environment
    int rank, size, namelen;
    MPI_Status info;
    char name[MPI_MAX_PROCESSOR_NAME];
    MPI_Comm_rank (MPI_COMM_WORLD, &rank); // ID of current process
    MPI_Get_processor_name (name, &namelen); // Hostname of node                                                                     
    MPI_Comm_size (MPI_COMM_WORLD, &size); // Number of processes

    char valueRec[10];
    char keyRec[10];

    if (rank == 0) {
        multimap<int, string> dictionary0;
        for (int i = 10; i < 15; i++) {
            string value = "valor" + to_string(i);
            dictionary0.insert(pair<int, string>(i, value));
        }
        for(int i = 0; i < 9; i++){
            MPI_Recv(&valueRec, 10, MPI_CHAR, 1, 0, MPI_COMM_WORLD, &info);
            MPI_Recv(&keyRec, 10, MPI_CHAR, 1, 0, MPI_COMM_WORLD, &info);
            dictionary0.insert(pair<int, string>(atoi(keyRec), valueRec));
        }
        multimap<int, string>::iterator itr;
        for (itr = dictionary0.begin(); itr != dictionary0.end(); ++itr) {
            cout << itr->first << '\t' << itr->second << '\n';
        }
        printf("Hello World from rank %d running on %s!\n", rank, name);
    }
    
    if (rank == 1) {
        multimap<int, string> dictionary1;
        for (int i = 0; i < 9; i++) {
            string value = "valor" + to_string(i);
            dictionary1.insert(pair<int, string>(i, value));
        }
        multimap<int, string>::iterator itr;
        for (itr = dictionary1.begin(); itr != dictionary1.end(); ++itr) {
            cout << itr->first << '\t' << itr->second << '\n';
        }
        for (itr = dictionary1.begin(); itr != dictionary1.end(); ++itr) {
            string key = to_string(itr->first);
            char *keyAux = &key[0u];
            string value = itr->second;
            char *valueAux = &value[0u];
            MPI_Send(valueAux, strlen(valueAux), MPI_CHAR, 0, 0, MPI_COMM_WORLD);
            MPI_Send(keyAux, strlen(keyAux), MPI_CHAR, 0, 0, MPI_COMM_WORLD);
        }
        printf ("Hello World from rank %d running on %s!\n", rank, name);
    }
    
    if (rank == 2) {
        multimap<int, string, greater<int> > dictionary2;
        printf ("Hello World from rank %d running on %s!\n", rank, name);
    }

    MPI_Barrier(MPI_COMM_WORLD);
    MPI_Finalize (); // Terminate MPI environment
}
