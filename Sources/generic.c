#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../Headers/structures.h"
#include "../Headers/generic.h"

void *safeMalloc(int sizeof_, char *errorMessage)
{
	void *malloc_ = malloc(sizeof_);
	if(malloc_ == NULL)
	{
		printf("<safeMalloc> Error: %s\n", errorMessage);
		return 0;
	}
	else return malloc_;
}

void *safeRealloc(void *ptr, int sizeof_, char *errorMessage)
{
	void *realloc_ = realloc(ptr, sizeof_);
	if(realloc_ == NULL)
	{
		printf("<safeRealloc> Error: %s\n", errorMessage);
		return 0;
	}
	else return realloc_;
}

void *safeAlloc(void *ptr, int sizeof_, char *errorMessage)
{
	if(ptr == NULL)
	{
		//printf("safealloc:malloc\n");
		return safeMalloc(sizeof_, errorMessage);
	}
	else 
	{
		//printf("safealloc:realloc\n");
		return safeRealloc(ptr, sizeof_, errorMessage);
	}
}

int array_search(char needle, char *haystack, int length)
{
	int i;
	for(i = 0; i < length; i++)
	{
		//printf("needle: %c // haystack[%d] = %c\n", needle, i, haystack[i]);
		if(haystack[i] == needle)
			return i;
	}
	return - 1;
}

char toLower(char char_)
{
	return char_ >= 'A' && char_ <= 'Z'
			? char_ + 'a' - 'A'
			: char_;
}

void strToLower(char* str)
{
	int i;
	for(i = 0; i < strlen(str); i++)
	{
		str[i] = toLower(str[i]);
	}
}

int random(int min, int max)
{
	if(min > max)
	{
		printf("min: %d\nmax: %d\n", min, max);
		return 0;
	}
	else
	{
		return (rand() % (max - min)) + min;
	}
}

int menu()
{
	char select[2];
	int intSelect;
	do
	{
		//[MENU_OPTIONS]
		printf("\t-----\tMain menu\t-----\t\n\n");
		printf("1.Play\n");
		printf("2.Edit game data\n");
		printf("3.Leave\n");
		
		//Value conversion
		scanf("%s", select);
		intSelect = atoi(select);
		
		system("cls");
	}while(intSelect > 3);
	return intSelect;
}
