#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define NUM_THREADS 4
#define FILE_SIZE 2000000
#define LINE_LEN 1025
#define ALPHABET_SIZE 26

char char_array[FILE_SIZE][LINE_LEN];
int max_char_array[FILE_SIZE];

void read_file() {
    char str[LINE_LEN];
    FILE *file = fopen("/homes/dan/625/wiki_dump.txt", "r");

    if (file == NULL) {
        perror("error");
        return;
    }

    for(int i = 1; i < FILE_SIZE; i++) {
        if (fgets(str, LINE_LEN, file) == NULL){
            break;
        }
        strcpy(char_array[i], str);
    }

    fclose(file);
}

void *max_char(int *myID) {
    char currChar, theChar;
    int array[FILE_SIZE];

    int startPos = ((int) myID) * (FILE_SIZE / NUM_THREADS);
    int endPos = startPos + (FILE_SIZE / NUM_THREADS);

    for (int i = startPos; i < endPos; i++) {
        for (int j = 0; j < LINE_LEN; j++) {
            currChar = char_array[i][j];
            if ((int)theChar < (int)currChar) {
                theChar = currChar;
            }
        }
        array[i] = ((int)theChar);
        theChar = '0';
    }

    for(int i = 0; i < FILE_SIZE; i++) {
        max_char_array[i] += array[i];
    }
}

void print_results()
{
    int i,j = 0;

    // then print out the totals
    for ( i = 0; i < FILE_SIZE; i++ ) {
        printf(" %d: %d\n", i, max_char_array[i]);
    }
}

int main(int argc, char* argv[]) 
{
	int i, rc;
	int numtasks, rank;
	MPI_Status Status;


	rc = MPI_Init(&argc,&argv);
	if (rc != MPI_SUCCESS) {
	  printf ("Error starting MPI program. Terminating.\n");
          MPI_Abort(MPI_COMM_WORLD, rc);
        }

        MPI_Comm_size(MPI_COMM_WORLD,&numtasks);
        MPI_Comm_rank(MPI_COMM_WORLD,&rank);

	printf("size = %d rank = %d\n", numtasks, rank);
	fflush(stdout);

	if ( rank == 0 ) {
		read_file();
	}
	MPI_Bcast(char_array, FILE_SIZE * LINE_LEN, MPI_CHAR, 0, MPI_COMM_WORLD);
	
	max_char(&rank);

	MPI_Reduce(char_array, max_char_array, ALPHABET_SIZE, MPI_INT, MPI_SUM, 0, MPI_COMM_WORLD);

	if ( rank == 0 ) {
		print_results();
	}

	MPI_Finalize();

	printf("Main: program completed. Exiting.\n");

	return 0;
}

