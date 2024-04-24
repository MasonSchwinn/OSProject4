#include <omp.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define NUM_THREADS 4
#define FILE_SIZE 1000000 // number of lines in the file 
#define LINE_LEN 1025 // length of each line in the file

char char_array[FILE_SIZE][LINE_LEN];
int max_char_array[FILE_SIZE];

void read_file();
void max_char(int myID);
void print_results();

void read_file() {
    char str[LINE_LEN];
    FILE *file = fopen("/homes/dan/625/wiki_dump.txt", "r");

    if (file == NULL) {
        perror("error");
        return;
    }

    for(int i = 0; i < FILE_SIZE; i++) {
        if (fgets(str, LINE_LEN, file) == NULL){
            break;
        }
        strcpy(char_array[i], str);
    }

    for (int i = 0; i < FILE_SIZE; i++ ) {
        max_char_array[i] = 0;
    }

    fclose(file);
}

void max_char(int myID) {
    char currChar, theChar;

    int startPos = ((myID) * FILE_SIZE) / NUM_THREADS;
    int endPos = (((myID) + 1) * FILE_SIZE) / NUM_THREADS;

    for (int i = startPos; i < endPos; i++) {
        for (int j = 0; j < LINE_LEN; j++) {
            currChar = char_array[i][j];
            if ((int)theChar < (int)currChar) {
                theChar = currChar;
            }
        }
        max_char_array[i] = ((int)theChar);
        theChar = '0';
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

int main() 
{
    read_file();

    omp_set_num_threads(NUM_THREADS);

    #pragma omp parallel 
    {
        max_char(omp_get_thread_num());
    }

    print_results();

	printf("Main: program completed. Exiting.\n");

    return 0;
}

