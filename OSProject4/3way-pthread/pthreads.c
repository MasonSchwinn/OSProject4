#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define NUM_THREADS 4
#define FILE_SIZE 2000000 // number of lines in the file 
#define LINE_LEN 1025 // length of each line in the file

pthread_mutex_t mutexsum;			// mutex for max_char
char char_array[FILE_SIZE][LINE_LEN];
int max_char_array[FILE_SIZE];

void read_file() {
    pthread_mutex_init(&mutexsum, NULL);
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

    pthread_mutex_lock(&mutexsum);
    for(int i = 0; i < FILE_SIZE; i++) {
        max_char_array[i] += array[i];
    }
    pthread_mutex_unlock(&mutexsum);

    pthread_exit(NULL);
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

int main() {
	int i, rc;
	pthread_t threads[NUM_THREADS];
	pthread_attr_t attr;
	void *status;


	/* Initialize and set thread detached attribute */
	pthread_attr_init(&attr);
	pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_JOINABLE);

	read_file();

	for (i = 0; i < NUM_THREADS; i++ ) {
		rc = pthread_create(&threads[i], &attr, max_char, (void *)i);
		if (rc) {
			printf("ERROR; return code from pthread_create() is %d\n", rc);
			exit(-1);
		}
	}

	/* Free attribute and wait for the other threads */
	pthread_attr_destroy(&attr);
	for(i=0; i<NUM_THREADS; i++) {
		rc = pthread_join(threads[i], &status);
		if (rc) {
			printf("ERROR; return code from pthread_join() is %d\n", rc);
			exit(-1);
		}
	}

	print_results();

	pthread_mutex_destroy(&mutexsum);
	printf("Main: program completed. Exiting.\n");
	pthread_exit(NULL);

    return 0;
}