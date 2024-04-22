#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define FILE_SIZE 1000000
#define LINE_LEN 1025

char char_array[FILE_SIZE][LINE_LEN];
int max_char_array[FILE_SIZE];

void max_char(int startPos, int endPos) {
    char str[LINE_LEN];
    FILE *file = fopen("/homes/dan/625/wiki_dump.txt", "r");
    if (file == NULL) {
        perror("error");
        return;
    }
    for(int i = 0; i < FILE_SIZE; i++) {
        if (fgets(str, LINE_LEN, file) == NULL) {
            break;
        }
        strcpy(char_array[i], str);
    }
    fclose(file);

    char currChar, theChar;
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

    int startPos = (rank) * (FILE_SIZE / numtasks);
    int endPos = (rank + 1) * (FILE_SIZE / numtasks);
    
    printf("size = %d rank = %d\n", numtasks, rank);

    max_char(startPos, endPos);

    MPI_Allreduce(MPI_IN_PLACE, max_char_array, FILE_SIZE, MPI_INT, MPI_MAX, MPI_COMM_WORLD);

    if (rank == 0) {
        for (int i = 0; i < FILE_SIZE; i++ ) {
            if (max_char_array[i] != '0' && max_char_array[i] != '\0'){
                printf(" %d: %d\n", i, max_char_array[i]);
            } else {
                printf("ERR\n");
            }
        }
    }    

    MPI_Finalize();
    
    return 0;
}