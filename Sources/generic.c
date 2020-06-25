#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>

#include "../Headers/main.h"

void *safeMalloc(int sizeof_, char *errorMessage)
{
	void *malloc_ = malloc(sizeof_);
	if(malloc_ == NULL)
	{
		#ifdef DEBUG
		printf("\n<safeMalloc> Error: %s\n", errorMessage);
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
		printf("\n<safeRealloc> Error: %s\n", errorMessage);
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
	unsigned int i;
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
	unsigned int i;
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
		printf("<mkSdir> Error: Path length shall be 1024 characters long, it's %u to much (%u)\n[path]: %s\n", sizeof(path) - 1024, sizeof(path), path);
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

long long int grabInt(char* instructions)
{
	int ret = 0;

	if (instructions != NULL)
		printf(instructions);

	scanf("%d", &ret);
	getchar();

	return ret;
}

float grabFloat(char* instructions)
{
	float ret = 0;

	if (instructions != NULL)
		printf(instructions);

	scanf("%f", &ret);
	getchar();

	return ret;
}

void displayTime(unsigned long long int time)
{
	char weekDay[10] = "\0";
	switch (secondsTo("day", time))
	{
		case 0:
			strcpy(weekDay, "monday");
			break;

		case 1:
			strcpy(weekDay, "tuesday");
			break;

		case 2:
			strcpy(weekDay, "wednesday");
			break;

		case 3:
			strcpy(weekDay, "thursday");
			break;

		case 4:
			strcpy(weekDay, "friday");
			break;

		case 5:
			strcpy(weekDay, "saturday");
			break;

		case 6:
			strcpy(weekDay, "sunday");
			break;

		default:
			strcpy(weekDay, "unknown");
	}

	printf(
		"Week %u, %s, %u:%u:%u",
		secondsTo("week", time),
		weekDay,
		secondsTo("hour", time),
		secondsTo("minute", time),
		secondsTo("second", time)
	);
}

unsigned long long int grabDateTime(char* instructions)
{
	unsigned int weeks = 0, days = 0, hours = 0, minutes = 0, seconds = 0;
	unsigned long long int ret = 0;

	if(instructions != NULL)
		printf(instructions);
	
	//Grabbing
	printf("\nWeek number: ");
	scanf("%u", &weeks);
	getchar();

	printf("Day: \n\t1.Monday\n\t2.Tuesday\n\t3.Wednsesday\n\t4.Thursday\n\t5.Friday\n\t6.Saturday\n\t7.Sunday\n\n");
	scanf("%u", &days);
	getchar();

	printf("Hours: ");
	scanf("%u", &hours);
	getchar();

	printf("Minutes: ");
	scanf("%u", &minutes);
	getchar();

	printf("Seconds: ");
	scanf("%u", &seconds);
	getchar();

	//Conversion
	ret = 
		(unsigned long long int)seconds + 
		(unsigned long long int)minutes * SECONDS_PER_MINUTE + 
		(unsigned long long int)hours * SECONDS_PER_HOUR + 
		(unsigned long long int)(days - 1) * SECONDS_PER_DAY + 
		(unsigned long long int)weeks * SECONDS_PER_WEEK;

	return ret;
}

unsigned int secondsTo(char *returnType, unsigned long long int duration_s)
{
	unsigned int ret = 0;
	
	//strToLower(returnType);

	if (!strcmp(returnType, "week") || !strcmp(returnType, "weeks"))
	{
		ret = duration_s / SECONDS_PER_WEEK;
	}
	else if(!strcmp(returnType, "day") || !strcmp(returnType, "days"))
	{
		duration_s = duration_s % SECONDS_PER_WEEK;
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
