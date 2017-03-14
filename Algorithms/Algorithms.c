#include <stdio.h>
#include <string.h>
#include <time.h>
#include <stddef.h>
#include <math.h>
#include <stdlib.h>
#include "sort.h"
#include "utilities.h"

typedef union {
	float f;
	struct {
		unsigned int mantisa : 23;
		unsigned int exponent : 8;
		unsigned int sign : 1;
	} parts;
} float_raw;

/* Default generator variables */
float min = -1000000.0, max = 1000000.0;

int parseVariables(int argc, char **argv, int *read, int *write, int *amount, int *loops);
void userMode();
void test(int number);
void run(int amount, int print, int loops);
void runFromFile(char fileName[], int print);

/** Parses command line variables, e.g. "./algorithm.exe -s 10000" */
int parseVariables(int argc, char **argv, int *read, int *write, int *amount, int *loops) {
	int found = 0;
	/* No command line variables */
	if (argc <= 1) {
		return 0;
	}
	/* For every variable check if correct syntax */
	for (int i = 0; i < argc; i++) {
		/* Number of elements to generate */
		if (strcmp(argv[i], "-s") == 0) {
			*amount = atoi(argv[i + 1]);
			found = 1;
		}
		/* Minimum random number size */
		if (strcmp(argv[i], "-min") == 0) {
			min = (float) atof(argv[i + 1]);
			found = 1;
		}
		/* Maximum random number size */
		if (strcmp(argv[i], "-max") == 0) {
			max = (float) atof(argv[i + 1]);
			found = 1;
		}
		/* Read mode to generate */
		if (strcmp(argv[i], "-r") == 0) {
			*read = 1;
			found = 1;
		}
		/* Write mode, amount of numbers to generate */
		if (strcmp(argv[i], "-w") == 0) {
			*write = 1;
			*amount = atoi(argv[i + 1]);
			found = 1;
		}
		/* Times to run loop */
		if (strcmp(argv[i], "-l") == 0) {
			*loops = atoi(argv[i + 1]);
			found = 1;
		}
	}
	return found;
}

/** Runs a loop asking user to input amount to process */
void userMode() {
	int input;

	do {
		/* Asks for input */
		printf(
			"\nEnter which test to perform:\n	 1. Sort list of certain length,\n	 2. Sort list with equal elements,\n	 3. Sort minus zero, positive / negative infinity,\n	 4. Sort NaN(s).\n	 5. Sorting algorithm time\n	 6. Generate data to file\n	 7. Read and sort from file\n	-1. Exit\nChoice: "
		);

		//printf("\nEnter number of elements to generate and process (max 1E+4; '-1' to exit): ");
		scanf("%d", &input);

		/* Breaks on quit */
		if (input < 0) {
			break;
		}

		/* Runs procedure */
		test(input);

	} while (input >= 0);

}

/** Runs appropriate test depending on userchoice */
void test(int number) {
	int input, print;

	float manual;
	float data[1000];
	int count = 0;

	switch (number) {
		/* Sort list of certain length */
		case 1:
			printf("\nEnter number of elements: ");
			scanf("%d", &input);

			//printf("\nPrint elements? 1 for yes, 0 for no: ");
			//scanf("%d", &print);
			print = 1;

			run(input, print, 1);
			break;
		/* Sort list with equal elements */
		case 2:
			do {
				printf("Enter %d element (-1 to stop): ", (count + 1));
				scanf("%f", &manual);
				if (manual != -1) {
					data[count] = manual;
					count++;
				}
			} while (manual != -1);

			//printf("\nPrint elements? 1 for yes, 0 for no: ");
			//scanf("%d", &print);
			print = 1;

			sort(data, count, print);
			break;
		/* Sort minus zero, positive / negative infinity */
		case 3:
			data[0] = 10;
			data[1] = -20;
			data[2] = 7;
			data[3] = -INFINITY;
			data[4] = -2017;
			data[5] = 0;
			data[6] = -1.0 * 0.0;
			data[7] = INFINITY;

			sort(data, 8, 1);

			break;
		/* Sort NaN(s) */
		case 4:

			data[0] = NAN;

			float_raw d1, d2, d3;
			d1.parts.sign = 1;
			d1.parts.exponent = 255;
			d1.parts.mantisa = 20000;
			d2.parts.sign = 1;
			d2.parts.exponent = 255;
			d2.parts.mantisa = 70;
			d3.parts.sign = 1;
			d3.parts.exponent = 255;
			d3.parts.mantisa = 8000;

			data[1] = d1.f;
			data[2] = 10;
			data[3] = -20;
			data[4] = 7;
			data[5] = NAN;
			data[6] = -2017;
			data[7] = 0;
			data[8] = d2.f;
			data[9] = d3.f;

			sort(data, 10, 1);

			break;
		/* Sorting algorithm time */
		case 5:
			printf("\nEnter number of elements: ");
			scanf("%d", &input);
			run(input, 0, 1);
			break;
		/* Generate data to file */
		case 6:
			printf("\nEnter number of elements: ");
			scanf("%d", &input);
			generateToFile("data.txt", input, &min, &max);
			break;
		/* Read and sort from file */
		case 7:
			runFromFile("data.txt", 1);
			break;
		/* Unrecognised */
		default:
			printf("Invalid selection.\n");
			break;
	}

}

/** Calls appropriate functions to generate and sort the data */
void run(int amount, int print, int loops) {

	float *data = (float *) malloc(sizeof(float) * amount);
	
	for (int i = 0; i < loops; i++) {

		/* Fill array with data */
		generate(data, amount, &min, &max);

		/* Call sorting algorithm */
		sort(data, amount, print);

	}

}

void runFromFile(char fileName[], int print) {

	FILE *file = fopen(fileName, "r");

	if (file == NULL) {
		return;
	}

	char line[128] = "\0";
	
	float data[250000];
	int count = 0;

	while (fgets(line, sizeof(line), file) != NULL) {
		data[count++] = atof(line);
	}

	sort(data, count, 1);

	return;
}

int main(int argc, char **argv) {
	int amount = 0, read = 0, write = 0, loops = 1;
	/* Check command line variables */
	if (!parseVariables(argc, argv, &read, &write, &amount, &loops)) {
		//printf("No command line variables detected, running in user mode.\n");
		userMode();
	}
	else {
		if (write) {
			generateToFile("batch.txt", amount, &min, &max);
		}
		else if (read) {
			runFromFile("batch.txt", 0);
		}
		else {
			run(amount, 0, loops);
		}
	}
    return 0;
}

