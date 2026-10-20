/*
 * Write a C program that creates a text file named info.txt in write mode. The program should take the user’s name and age as input, and write them to the file using fprintf(). After writing, display a message confirming that the data was successfully saved.
 */
#ifdef __MINGW32__
#ifndef __USE_MINGW_ANSI_STDIO
#define __USE_MINGW_ANSI_STDIO 1
#endif
#endif
#include <ctype.h>
#include <errno.h>
#include <limits.h>
#include <math.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static int parse_long_long(const char *text, long long *value) {
    char *end;
    long long parsed;
    errno = 0;
    parsed = strtoll(text, &end, 10);
    if (errno == ERANGE || end == text || *end != '\0') return 0;
    *value = parsed;
    return 1;
}

static int read_long_long(long long *value) {
    char token[128];
    return scanf("%127s", token) == 1 && parse_long_long(token, value);
}

static int read_unsigned_long_long(unsigned long long *value) {
    char token[128];
    char *end;
    unsigned long long parsed;
    if (scanf("%127s", token) != 1 || token[0] == '-') return 0;
    errno = 0;
    parsed = strtoull(token, &end, 10);
    if (errno == ERANGE || end == token || *end != '\0') return 0;
    *value = parsed;
    return 1;
}

int main(void) {
    char name[100];
    int age;
    FILE *file;
    if (scanf(" %99[^\n]", name) != 1 || scanf("%d", &age) != 1 || age < 0 || age > 150) {
        fprintf(stderr, "Enter a name and a valid age (0..150).\n"); return 1;
    }
    file = fopen("info.txt", "w");
    if (file == NULL) { perror("info.txt"); return 1; }
    {
        int write_failed = fprintf(file, "Name: %s\nAge: %d\n", name, age) < 0;
        int close_failed = fclose(file) != 0;
        if (write_failed || close_failed) { perror("Writing info.txt"); return 1; }
    }
    puts("Data saved successfully.");
    return 0;
}
