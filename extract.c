// Functions and types used to extract x,y,z values from a string
// containing a URL of the form:
// "http://almondbread.cse.unsw.edu.au/mandelbrot/2/5/3.14/-0.141/tile.bmp"
//
// z5184991
// Written on 2017-09-??
// Tutor (dayHH-lab)

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "extract.h"

#define NUMBER_OF_SLASHES_BEFORE_Z_COORD 5
#define NUMBER_OF_SLASHES_BEFORE_X_COORD 6
#define NUMBER_OF_SLASHES_BEFORE_Y_COORD 7

#define MAX_ARRAY_SIZE 1000

void extractHelp (char *message, char *valuestring, int numberOfSlashesBeforeValue);

int main (int argc, char *argv[]) {

    char *message = "http://almondbread.cse.unsw.edu.au/mandelbrot/2/5/3.14/-0.141/tile.bmp";

    triordinate dat = extract (message);

    printf ("dat is (%f, %f, %d)\n", dat.x, dat.y, dat.z);

    assert (dat.x == 3.14);
    assert (dat.y == -0.141);
    assert (dat.z == 5);

    return EXIT_SUCCESS;
}

triordinate extract (char *message) {
// Define triordinate to be returned
	triordinate zxyTriordinate;

	char zValue[MAX_ARRAY_SIZE] = {0};
	char xValue[MAX_ARRAY_SIZE] = {0};
	char yValue[MAX_ARRAY_SIZE] = {0};

	extractHelp(&message, &zValue, NUMBER_OF_SLASHES_BEFORE_Z_COORD);
	extractHelp(&message, &xValue, NUMBER_OF_SLASHES_BEFORE_X_COORD);
	extractHelp(&message, &yValue, NUMBER_OF_SLASHES_BEFORE_Y_COORD);

	long int z = myAtoL(zArray);
    double x = myAtoD(xArray);
    double y = myAtoD(yArray);

    zxyTriordinate.z = z;
    zxyTriordinate.x = x;
    zxyTriordinate.y = y;

    return zxyTriordinate;
}

double myAtoD (char *message) {
    double currentNumber = 0;
    int i = 0;
    int sizeArray = 0, decimalIndex = 0;
    int negative = FALSE;

    while(message[sizeArray] != '\0'){
        sizeArray++;
    }
    while(message[decimalIndex] != '.'){
        decimalIndex++;
    }
    int divideValue = 0;
    divideValue = sizeArray - decimalIndex - 1;


    if(message[i] == '-'){
        negative = TRUE;
        i++;
    }
    if(message[i] >= '0' && message[i] <= '9'){
        currentNumber = message[i] - '0';
        i++;
    }
    while(message[i] >= '0' && message[i] <= '9'){
        currentNumber = 10*currentNumber + message[i] - '0';
        i++;
    }

    if(message[i] == '.'){
        i++;
    }

    while(message[i] >= '0' && message[i] <= '9'){
        currentNumber = 10*currentNumber + message[i] - '0';
        i++;
    }

    int j = 1;
    while(j <= divideValue){
        currentNumber *= 0.1;
        j++;
    }

    if(negative == TRUE){
        currentNumber = -1*currentNumber;
    }

    return currentNumber;

}

long myAtoL (char *message) {
    int currentNumber = 0;
    int i = 0;
    int negative = FALSE;

    if(message[i] == '-'){
        negative = TRUE;
        i++;
    }
    if(message[i] >= '0' && message[i] <= '9'){
        currentNumber = message[i] - '0';
        i++;
    }
    while(message[i] >= '0' && message[i] <= '9'){
        currentNumber = 10*currentNumber + message[i] - '0';
        i++;
    }
    if(negative){
        currentNumber = -1*currentNumber;
    }

    return currentNumber;
}


void extractHelp (char *message, char *valuestring, int numberOfSlashesBeforeValue) {

// Find the starting position of value
	int slashCount = 0;
	int currentPosition = 0;
	while (slashCount < numberOfSlashesBeforeValue) {
		if (message[currentPosition] == '/') {
			slashCount++;
			currentPosition++;
		}
	}

	int valueStartPosition = currentPosition;

// Find char length of value
	while (message[currentPosition] != '/') {
		currentPosition++;
	}

	int valueEndPosition = currentPosition;
	int valueLength = valueEndPosition - valueStartPosition;

// Create string of extracted value
	int i = 0;
	while (i < valueLength) {
		valuestring[i] = message[valueStartPosition + i];
		i++;
	}

	valuestring[i] = '\0';

	*valuestring = calloc(1, sizeOf(*valuestring));
}