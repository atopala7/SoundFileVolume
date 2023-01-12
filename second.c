#include <stdio.h>
#include <stdint.h>
#include <time.h>
#include <stdlib.h>

#define MAX 65536
#define HALF 32768 
#define OUTPUT "output.raw"


int16_t adjustVolume(int16_t sample, float factor) {
	return (int16_t)(sample * factor);
}

int16_t adjustVolume2(int16_t sample, float factor) {
	static int16_t* lookupTable = NULL;
	static float oldFactor = 0;
	if (factor != oldFactor) {
		clock_t t = clock();
		oldFactor = factor;
		printf("Creating lookup table...\n");
		if (lookupTable) {
			free(lookupTable);
		}
		lookupTable = (int16_t*)malloc(MAX*sizeof(int16_t));
		int i;
		for (i=0; i<MAX; i++) {
			// Offset i by half the maximum value of an unsigned int16_t to fill the table with all the possible signed int16_t values
			lookupTable[i] = (int16_t)((i-HALF) * factor);	
		}
		t = clock() - t;
		printf("Took %d cycles (%f seconds) to create the lookup table.\n", t, (float)t/CLOCKS_PER_SEC);
	}
	return lookupTable[sample + HALF];
}

int main(int argc, char *argv[]) {
	int i;
	int j;
	clock_t t;
	
	// Pointers to input and output files
	FILE *fp;
	FILE *fp2;

	// Array to contain all the samples
	int16_t *samples;

	// The size of the imput file
	long size;
	// Number of sound samples in the input file
	int numSamples;
	
	float volumeFactor;

	fp = fopen(argv[1], "r");
	fp2 = fopen(OUTPUT, "w");

	// Find the size (in bytes) of the input file
	fseek(fp, 0L, SEEK_END);
	size = ftell(fp);
	fseek(fp, 0L, SEEK_SET);
	
	// Divide the file size into chunks of int16_t
	numSamples = size / sizeof(int16_t); 

	// Read all the samples from the file into memory
	samples = (int16_t*)malloc(numSamples*sizeof(int16_t));
	fread(samples, sizeof(int16_t), numSamples, fp);

	volumeFactor = 1.0;

	samples[0] = adjustVolume2(samples[0], volumeFactor);

	printf("Number of samples from sound file: %d\n", numSamples);
	t = clock();	
	for (i=0; i<numSamples; i++) {
		samples[i] = adjustVolume2(samples[i], volumeFactor);
	}
	t = clock() - t;

	printf("%d cycles (%f seconds)\n", t, (float)t/CLOCKS_PER_SEC);

	// Write the adjusted samples to the output file
	fwrite(samples, sizeof(int16_t), numSamples, fp2);

	free(samples);

	fclose(fp);
	fclose(fp2);

	return 0;
}
