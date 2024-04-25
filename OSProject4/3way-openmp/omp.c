#include <omp.h>
#include <stdio.h>
#include <stdlib.h>

#define NUM_THREADS 4
#define FILE_SIZE 2000000 // number of lines in the file 
#define LINE_LEN 1025 // length of each line in the file

char char_array[FILE_SIZE][LINE_LEN+1];
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

    int i = 0;
    while (fgets(str, LINE_LEN, file) != NULL && i < FILE_SIZE) {
        snprintf(char_array[i], LINE_LEN, "%s", str);
        i++;
    }

    fclose(file);
}

void max_char(int myID) {
    int startPos = (myID * FILE_SIZE) / NUM_THREADS;
    int endPos = ((myID + 1) * FILE_SIZE) / NUM_THREADS;

    for (int i = startPos; i < endPos; i++) {
        int max_char = 0;
        for (int j = 0; char_array[i][j] != '\0'; j++) {
            if ((int)char_array[i][j] > max_char) {
                max_char = (int)char_array[i][j];
            }
        }
        max_char_array[i] = (int)max_char;
    }
}

void print_results() {
    for (int i = 0; i < FILE_SIZE; i++) {
        if (max_char_array[i] != 0) {
            printf("%d: %d\n", i, max_char_array[i]);
        }
    }
}

int main() {
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
