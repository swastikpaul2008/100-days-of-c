/*
 * Write a program that accepts a percentage (0-100) and assigns a grade based on the following criteria: 
 * 90-100: Grade A 
 * 80-89: Grade B 
 * 70-79: Grade C 
 * 60-69: Grade D 
 * below 60: Grade F.
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
    double percentage;
    if (scanf("%lf", &percentage) != 1 || !isfinite(percentage) ||
        percentage < 0.0 || percentage > 100.0) {
        fprintf(stderr, "Percentage must be from 0 to 100.\n");
        return 1;
    }
    puts(percentage >= 90 ? "Grade A" : percentage >= 80 ? "Grade B" :
         percentage >= 70 ? "Grade C" : percentage >= 60 ? "Grade D" : "Grade F");
    return 0;
}
