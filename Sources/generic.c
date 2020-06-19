#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#ifdef _MSC_VER
	#include <direct.h>
#endif

#include "../Headers/main.h"

void *safeMalloc(int sizeof_, char *errorMessage)
{
	void *malloc_ = malloc(sizeof_);
	if(malloc_ == NULL)
	{
		#ifdef DEBUG
		printf("<safeMalloc> Error: %s\n", errorMessage);
		#endif
		return 0;
	}
	else 
	{
		return malloc_;
	}
}

void *safeRealloc(void *ptr, int sizeof_, char *errorMessage)
{
	void *realloc_ = realloc(ptr, sizeof_);
	if(realloc_ == NULL)
	{
		#ifdef DEBUG
		printf("<safeRealloc> Error: %s\n", errorMessage);
		#endif
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

/*void freeHyper(int *mainHeader, unsigned int *lengths, unsigned int dimentions)
{
	if(dimentions > 0)
	{
		int i;
		for(i = 0; i < lengths[0]; i++)
		{
			freeHyper(mainHeader[i], &lengths[1], dimentions - 1);
			free(mainHeader);
		}
	}
}*/

void freeMatress(void **mainHeader, unsigned int headersLength)
{
	int i;
	for(i = 0; i < headersLength; i++)
		free(mainHeader[i]);
	//freeHyper(mainHeader, &headersLength, 2);
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
		#ifdef DEBUG
		printf("min: %d\nmax: %d\n", min, max);
		#endif
		return 0;
	}
	else
	{
		return (rand() % (max - min)) + min;
	}
}

int mkSdir(char *path)
{
	if(sizeof(path) > 1024)
	{
		printf("<mkSdir> Error: Path length shall be 1024 characters long, it's %d to much (%d)\n[path]: %s\n", sizeof(path) - 1024, sizeof(path), path);
	}
	
	char 
		*folder = NULL,
		existingPath[1024] = "\0", 
		separator[2] = "/",
		*_path = safeMalloc(sizeof(char) * (strlen(path) + 1), "mkSdir/path copy");
	int ret = 0, sizeofExistingPath = 0;
	DIR *dir_;
	
	strcpy(_path, path);
	
	folder = strtok(_path, separator);
	while(folder != NULL)
	{
		strcat(existingPath, folder);
		strcat(existingPath, separator);
		//printf("-%s\n", existingPath);
		
		if(dir_ = opendir(existingPath))
			closedir(dir_);
		else
		{
			//If it needs to be created
			#ifdef _MSC_VER
				ret = _mkdir(existingPath);
			#else
				ret = mkdir(existingPath);
			#endif
			
			#ifdef DEBUG
			if(ret != -1)
				printf("<mkSdir> %s created\n", existingPath);
			else
				printf("<mkSdir> Error: couldn't create %s\n", existingPath);
			#endif
		}
		
		folder = strtok(NULL, separator);
	}

	free(_path);
	return ret;
}

unsigned int secondsTo(char *returnType, unsigned int duration_s)
{
	unsigned int ret = 0;
	
	//strToLower(returnType);
	
	if(!strcmp(returnType, "day") || !strcmp(returnType, "days"))
	{
		ret = duration_s / SECONDS_PER_DAY;
	}
	else if(!strcmp(returnType, "hour") || !strcmp(returnType, "hours"))
	{
		duration_s = duration_s % SECONDS_PER_DAY;
		ret = duration_s / SECONDS_PER_HOUR;
	}
	else if(!strcmp(returnType, "minute") || !strcmp(returnType, "minutes"))
	{
		duration_s = duration_s % SECONDS_PER_HOUR;
		ret = duration_s / SECONDS_PER_MINUTE;
	}
	else if(!strcmp(returnType, "second") || !strcmp(returnType, "seconds"))
	{
		ret = duration_s % SECONDS_PER_MINUTE;
	}
	else 
	{
		#ifdef DEBUG
		printf("<secondsTo> unknown time unity: %s\n", returnType);
		#endif
	}
	
	return ret;
}
