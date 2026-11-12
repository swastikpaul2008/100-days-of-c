/*
 * Write a function that accepts a structure as parameter and prints its members.
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

struct Student { char name[100]; int roll; double marks; };
static void print_student(struct Student student) {
    printf("%s %d %.2f\n", student.name, student.roll, student.marks);
}
int main(void) {
    struct Student student;
    if (scanf("%99s %d %lf", student.name, &student.roll, &student.marks) != 3 ||
        student.roll < 0 || !isfinite(student.marks) || student.marks < 0.0 || student.marks > 100.0) {
        fprintf(stderr, "Invalid student record.\n"); return 1;
    }
    print_student(student);
    return 0;
}
