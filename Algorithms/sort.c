#include <math.h>
#include "sort.h"

typedef union {
	float f;
	struct {
		unsigned int mantisa : 23;
		unsigned int exponent : 8;
		unsigned int sign : 1;
	} parts;
} float_raw;

void printArray(float *data, int amount);

int compareFloat(float float1, float float2);
void quickSort(float *data, int low, int high);
int partition(float *data, int low, int high);

/** Prints array to console */
void printArray(float *data, int amount) {
	printf("\n");
	if (amount == 0) {
		printf("Empty array\n");
	}
	for (int i = 0; i < amount; i++) {
		if (isnan(data[i])) {
			float_raw d;
			d.f = data[i];
			printf("Element %d\t : NAN %d %d %d\n", (i + 1), d.parts.sign, d.parts.exponent, d.parts.mantisa);
		}
		else {
			printf("Element %d\t : %f\n", i + 1, data[i]);
		}
	}
}

/** Returns true if (float1 < float2) using assumed totallity */
int compareFloat(float float1, float float2) {
	/* Compares NaNs by their mantisas */
	if (isnan(float1) && isnan(float2)) {
		float_raw d1, d2;
		d1.f = float1;
		d2.f = float2;
		return (d1.parts.mantisa < d2.parts.mantisa);
	}

	/* NaN > +inf */
	if (isnan(float1)) {
		return 0;
	}
	if (isnan(float2)) {
		return 1;
	}

	/* -0 < 0 */
	if (float1 == 0 && float2 == 0) {
		float_raw d1, d2;
		d1.f = float1;
		d2.f = float2;
		return (d1.parts.sign && !(d2.parts.sign));
	}

	/* f1 < f2 */
	return (float1 < float2);
}

/** Main sorting method */
void sort(float *data, int amount, int print) {
	if (print) {
		printArray(data, amount);
	}

	/* Initial QuickSort call */
	quickSort(data, 0, (amount - 1));

	if (print) {
		printArray(data, amount);
	}
}

void quickSort(float *data, int low, int high) {
	if (low < high) {
		int p = partition(data, low, high);
		quickSort(data, low, p);
		quickSort(data, p + 1, high);
	}
}

int partition(float *data, int low, int high) {
	float pivot = data[low];
	int i = low - 1;
	int j = high + 1;

	while (1) {
		do {
			i++;
		} while (compareFloat(data[i], pivot));

		do {
			j--;
		} while (compareFloat(pivot, data[j]));

		if (i >= j) {
			return j;
		}

		float temp = data[i];
		data[i] = data[j];
		data[j] = temp;
	}
}