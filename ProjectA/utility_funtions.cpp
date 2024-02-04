// utility_functions
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string>
#include <time.h>
#include <Windows.h>

#include "Classes.h"
#include "fight_system.h"
#include "utility_funtions.h"

int textspeed = 5;

#define MINIWAIT 650

void chainread(const char* format, ...) {
	va_list args;
	va_start(args, format);

	for (const char* currentChar = format; *currentChar != '\0'; ++currentChar) {
		if (*currentChar == '%') {
			++currentChar;

			switch (*currentChar) {
			case 'd': {
				int value = va_arg(args, int);
				printf("%d", value);
				break;
			}
			case 's': {
				const char* str = va_arg(args, const char*);
				printf("%s", str);
				break;
			}
			default:
				putchar(*currentChar);
				break;
			}
		}
		else {
			putchar(*currentChar);
		}

		Sleep(textspeed*10);
	}

	va_end(args);
}

char inputChar() {
	char antwort;
	chainread("-> ");
	scanf_s("%c", &antwort, 1);
	while (getchar() != '\n');
	return antwort;
}

int inputZahl() {
	int antwort;
	chainread("-> ");
	scanf_s("%d", &antwort);
	while (getchar() != '\n');
	return antwort;
}

void waitPoint(int point) {

	for (int i = 0; i < point; i++) {
		printf(".");
		Sleep(MINIWAIT);
	}
}