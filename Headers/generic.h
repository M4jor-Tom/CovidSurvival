#pragma once

#define DEBUG

typedef enum menuOptions
{
	play,
	Edit,
	Quit
}menuOptions;

void *safeMalloc(int sizeof_, char* errorMessage);

void *safeRealloc(void *ptr, int sizeof_, char* errorMessage);

void *safeAlloc(void * ptr, int sizeof_, char* errorMessage);

int array_search(char needle, char *haystack, int length);

char toLower(char char_);

void strToLower(char* str);

int random(int min, int max);
