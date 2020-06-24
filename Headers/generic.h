#pragma once

#include <stdbool.h>

void *safeMalloc(int sizeof_, char *errorMessage);

void *safeRealloc(void *ptr, int sizeof_, char *errorMessage);

void *safeAlloc(void *ptr, int sizeof_, char *errorMessage);

//void freeHyper(int *mainHeader, unsigned int *lengths, unsigned int dimentions);

void freeMatress(void **mainHeader, unsigned int headersLength);

int array_search(char needle, char *haystack, int length);

char toLower(char char_);

void strToLower(char *str);

int random(int min, int max);

//Uses mkdir for each time there's a new shash in the string
int mkSdir(char *path);

long long int grabInt(char* instructions);

float grabFloat(char* instructions);

//Prints week#, week::day, hour:minute:second
void displayTime(unsigned long long int time);

unsigned long long int grabDateTime(char* instructions);

//Translates a duration in seconds to its corresponding time unity in an amount that can't be over its superior-unit increment
//Returns 0 if this unit contains more seconds than inputed
unsigned int secondsTo(char *returnType, unsigned int duration_s);
