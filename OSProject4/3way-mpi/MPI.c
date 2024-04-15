#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//#define NUM_THREADS 4
int NUM_THREADS;

#define FILE_SIZE 2000000
#define LINE_LEN 1025

char char_array[FILE_SIZE][LINE_LEN];
int max_char_array[FILE_SIZE];

void read_file() {
    char str[LINE_LEN];
    FILE *file = fopen("/homes/dan/625/wiki_dump.txt", "r");

    if (file == NULL) {
        perror("error");
        return;
    }

    for(int i = 0; i < FILE_SIZE; i++) { // Start from index 0
        if (fgets(str, LINE_LEN, file) == NULL) {
            break;
        }
        strcpy(char_array[i], str);
    }

    fclose(file);
}

void max_char(int *myID) {
    char currChar, theChar = 0;
    int array[FILE_SIZE];

    int startPos = ((*myID) * FILE_SIZE) / NUM_THREADS;
    int endPos = (((*myID) + 1) * FILE_SIZE) / NUM_THREADS;

    // Adjust endPos for the last thread
    if ((*myID) == NUM_THREADS - 1) {
        endPos = FILE_SIZE;
    }

    for (int i = startPos; i < endPos; i++) {
        theChar = 0; // Initialize theChar
        for (int j = 0; j < LINE_LEN; j++) {
            currChar = char_array[i][j];
            if ((int)theChar < (int)currChar) {
                theChar = currChar;
            }
        }
        max_char_array[i] = ((int)theChar);
    }
}

void print_results()
{
    int i,j = 0;

    // then print out the totals
    for ( i = 0; i < FILE_SIZE; i++ ) {
        if (max_char_array[i] != '0' && max_char_array[i] != '\0'){
            printf(" %d: %d\n", i, max_char_array[i]);
        }
    }
}

int main(int argc, char* argv[]) 
{
    int rc;
    int numtasks, rank;
    MPI_Status Status;

    rc = MPI_Init(&argc,&argv);
    if (rc != MPI_SUCCESS) {
        printf ("Error starting MPI program. Terminating.\n");
        MPI_Abort(MPI_COMM_WORLD, rc);
    }

    MPI_Comm_size(MPI_COMM_WORLD,&numtasks);
    MPI_Comm_rank(MPI_COMM_WORLD,&rank);

    NUM_THREADS = numtasks;
    printf("size = %d rank = %d\n", numtasks, rank);
    fflush(stdout);

    if (rank == 0) {
        read_file();
    }

    MPI_Bcast(char_array, FILE_SIZE * LINE_LEN, MPI_CHAR, 0, MPI_COMM_WORLD);

    max_char(&rank);

    if (rank == 0) {
        print_results();
    }

    MPI_Finalize();

    printf("Main: program completed. Exiting.\n");

    return 0;
}