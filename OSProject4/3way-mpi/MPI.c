#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define FILE_SIZE 2000000 // number of lines to be read from the file
#define LINE_LEN 1025 // length of the lines in the file

char char_array[FILE_SIZE][LINE_LEN]; 
int max_char_array[FILE_SIZE];

/*
* Reads in the wiki_dump file and finds the largest value ascii character in each line
* \param startPos given start position
* \param endPos given end position
*/
void max_char(int startPos, int endPos) {
    char str[LINE_LEN];
    FILE *file = fopen("/homes/dan/625/wiki_dump.txt", "r"); // opens file for reading
    if (file == NULL) { //checks if file exists
        perror("error");
        return;
    }

    for(int i = 0; i < FILE_SIZE; i++) { //reads each line from the given file and copies it to a char array
        if (fgets(str, LINE_LEN, file) == NULL) {
            break;
        }
        snprintf(char_array[i], LINE_LEN, "%s", str);
    }
    fclose(file); 

    char currChar, theChar;
    for (int i = startPos; i < endPos; i++) { //calculates the largest ascii value of each line and stores it in a int array
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

/*
* Main function utilizes mpi to parallelize computing
*/
int main(int argc, char* argv[]) 
{
    int rc;
    int numtasks, rank;
    MPI_Status Status;

    rc = MPI_Init(&argc,&argv); //initializes the MPI environment
    if (rc != MPI_SUCCESS) {
        printf ("Error starting MPI program. Terminating.\n");
        MPI_Abort(MPI_COMM_WORLD, rc);
    }

    MPI_Comm_size(MPI_COMM_WORLD,&numtasks); //gets the number of processes
    MPI_Comm_rank(MPI_COMM_WORLD,&rank); //determines the ranks of the processes

    int startPos = (rank) * (FILE_SIZE / numtasks);
    int endPos = (rank + 1) * (FILE_SIZE / numtasks);
    
    printf("size = %d rank = %d\n", numtasks, rank);

    max_char(startPos, endPos);

    MPI_Allreduce(MPI_IN_PLACE, max_char_array, FILE_SIZE, MPI_INT, MPI_MAX, MPI_COMM_WORLD); //applies a reduction calculation to all processes

    if (rank == 0) {
        for (int i = 0; i < FILE_SIZE; i++ ) {
            if (max_char_array[i] != '0' && max_char_array[i] != '\0'){
                printf(" %d: %d\n", i, max_char_array[i]);
            } else {
                printf("ERR\n");
            }
        }
    }    

    MPI_Finalize(); //terminates the MPI environment
    
    return 0;
}