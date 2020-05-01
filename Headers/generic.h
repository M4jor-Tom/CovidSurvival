#pragma once

#define DEBUG

void *safeMalloc(int sizeof_, char* errorMessage);

void *safeRealloc(void *ptr, int sizeof_, char* errorMessage);

void *safeAlloc(void * ptr, int sizeof_, char* errorMessage);

//void freeHyper(int *mainHeader, unsigned int *lengths, unsigned int dimentions);

void freeMatress(void **mainHeader, unsigned int headersLength);

int array_search(char needle, char *haystack, int length);

char toLower(char char_);

void strToLower(char* str);

int random(int min, int max);
