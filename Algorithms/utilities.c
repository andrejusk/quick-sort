#include "utilities.h"
#include <stdlib.h>  
#include <stdio.h>

/** Fills array with random floating point numbers within a specified range */
void generate(float *data, int amount, float *min, float *max) {
	float temp;
	/* For every element */
	for (int i = 0; i < amount; i++) {
		/* Generate random floating point within range */
		temp = (float)rand() / (float)(RAND_MAX / *max) * 2 + *min;
		data[i] = temp;
	}
}

/** Generates random floating point numbers within a specified range and saves them to a file*/
void generateToFile(char fileName[], int amount, float *min, float *max) {
	float temp;
	FILE *file = fopen(fileName, "w");
	/* For every element */
	for (int i = 0; i < amount; i++) {
		/* Generate random floating point within range */
		temp = (float)rand() / (float)(RAND_MAX / *max) * 2 + *min;
		fprintf(file, "%.6f", temp);
		if ((i + 1) != amount) {
			fprintf(file, "\n");
		}
	}
	fclose(file);
}