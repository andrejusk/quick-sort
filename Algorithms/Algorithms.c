#include <stdio.h>
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
int read = 0, write = 0, amount = 0, loops = 0;

int parseVariables(int argc, char **argv);
void userMode();
void test(int number);
void run(int amount, int print, int loops);
void runFromFile(char fileName[], int print);

/** Parses command line variables, e.g. "./algorithm.exe -s 10000" */
int parseVariables(int argc, char **argv) {
	int found = 0;
	/* No command line variables */
	if (argc <= 1) {
		return 0;
	}
	/* For every variable check if correct syntax */
	for (int i = 0; i < argc; i++) {
		/* Number of elements to generate */
		if (strcmp(argv[i], "-s") == 0) {
			amount = atoi(argv[i + 1]);
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
			read = 1;
			found = 1;
		}
		/* Write mode, amount of numbers to generate */
		if (strcmp(argv[i], "-w") == 0) {
			write = 1;
			amount = atoi(argv[i + 1]);
			found = 1;
		}
		/* Times to run loop */
		if (strcmp(argv[i], "-l") == 0) {
			loops = atoi(argv[i + 1]);
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
			"\nEnter which test to perform: \
			\n	 1. Sort list of certain length, \
			\n	 2. Sort list with equal elements, \
			\n	 3. Sort minus zero, positive / negative infinity, \
			\n	 4. Sort NaN(s). \
			\n	 5. Generate data to file \
			\n	 6. Read and sort from file \
			\n	-1. Exit \
			\nChoice: "
		);

		scanf("%d", &input);

		/* Breaks on quit */
		if (input < 0) {
			break;
		}

		/* Runs procedure */
		test(input);

	} while (input >= 0);

}

/** Runs appropriate test depending on user choice */
void test(int number) {
	int input, print;
	
	float edge_data[] = { 10, -20, 7, -INFINITY, -2017, 0, -1.0 * 0.0, INFINITY };

	float_raw d1, d2, d3;
	d1.parts.sign = d2.parts.sign = d3.parts.sign = 1;
	d1.parts.exponent = d2.parts.exponent = d3.parts.exponent = 255;
	d1.parts.mantisa = 2000;
	d2.parts.mantisa = 70;
	d3.parts.mantisa = 800;
	float nan_data[] = { NAN, d1.f, 10, -20, 7.50, NAN, -2017, d2.f, d3.f, 0 };

	float manual_data[1000];
	float manual;
	int count = 0;

	switch (number) {
		/* Sort list of certain length */
		case 1:
			printf("\nEnter number of elements: ");
			scanf("%d", &input);

			printf("\nPrint elements? 1 for yes, 0 for no: ");
			scanf("%d", &print);

			run(input, print, 1);
			break;
		/* Sort list with equal elements */
		case 2:
			if(1) {
			}
			do {
				printf("Enter %d element (-1 to stop): ", (count + 1));
				scanf("%f", &manual);
				if (manual != -1) {
					manual_data[count] = manual;
					count++;
				}
			} while (manual != -1);

			printf("\nPrint elements? 1 for yes, 0 for no: ");
			scanf("%d", &print);

			sort(manual_data, count, print);
			break;
		/* Sort minus zero, positive / negative infinity */
		case 3:
			sort(edge_data, 8, 1);
			break;
		/* Sort NaN(s) */
		case 4:
			sort(nan_data, 10, 1);
			break;
		/* Generate data to file */
		case 5:
			printf("\nEnter number of elements: ");
			scanf("%d", &input);
			generateToFile("data.txt", input, &min, &max);
			break;
		/* Read and sort from file */
		case 6:
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
	/* Allocates memory for data array */
	float *data = (float *) malloc(sizeof(float) * amount);
	/* Generates and sorts data as many times as requested */
	for (int i = 0; i < loops; i++) {
		/* Fill array with data */
		generate(data, amount, &min, &max);
		/* Call sorting algorithm */
		sort(data, amount, print);
	}
}

/** Reads data from file and sorts */
void runFromFile(char fileName[], int print) {
	/* Open file for reading */
	FILE *file = fopen(fileName, "r");
	if (file == NULL) {
		return;
	}

	char line[128] = "\0";
	float data[250000];
	int count = 0;

	/* Read data */
	while (fgets(line, sizeof(line), file) != NULL) {
		data[count++] = atof(line);
	}

	/* Sort data */
	sort(data, count, 1);
}

int main(int argc, char **argv) {
	/* Check command line variables */
	if (!parseVariables(argc, argv)) {
		userMode();
	}
	else {
		/* Generate variables to file */
		if (write) {
			generateToFile("batch.txt", amount, &min, &max);
		}
		/* Read variables from file and sort */
		else if (read) {
			runFromFile("batch.txt", 0);
		}
		/* Run with specified amount and iterations */
		else {
			run(amount, 0, loops);
		}
	}
    return 0;
}

