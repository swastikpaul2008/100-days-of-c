/*
 * Find and print the student with the highest marks.
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
    struct Student { char name[100]; int roll; double marks; } student, top;
    int count;
    if (scanf("%d", &count) != 1 || count < 1 || count > 1000) { fprintf(stderr, "Invalid student count.\n"); return 1; }
    for (int i = 0; i < count; ++i) {
        if (scanf("%99s %d %lf", student.name, &student.roll, &student.marks) != 3 ||
            student.roll < 0 || !isfinite(student.marks) || student.marks < 0.0 || student.marks > 100.0) {
            fprintf(stderr, "Invalid student record.\n"); return 1;
        }
        if (i == 0 || student.marks > top.marks) top = student;
    }
    printf("%s %d %.2f\n", top.name, top.roll, top.marks);
    return 0;
}
