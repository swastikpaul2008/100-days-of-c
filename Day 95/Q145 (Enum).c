/*
 * Return a structure containing top student's details from a function.
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
static struct Student top_student(struct Student students[], int count) {
    struct Student top = students[0];
    for (int i = 1; i < count; ++i) if (students[i].marks > top.marks) top = students[i];
    return top;
}
int main(void) {
    struct Student students[1000], top;
    int count;
    if (scanf("%d", &count) != 1 || count < 1 || count > 1000) { fprintf(stderr, "Invalid student count.\n"); return 1; }
    for (int i = 0; i < count; ++i)
        if (scanf("%99s %d %lf", students[i].name, &students[i].roll, &students[i].marks) != 3 ||
            students[i].roll < 0 || !isfinite(students[i].marks) || students[i].marks < 0.0 || students[i].marks > 100.0) {
            fprintf(stderr, "Invalid student record.\n"); return 1;
        }
    top = top_student(students, count);
    printf("%s %d %.2f\n", top.name, top.roll, top.marks);
    return 0;
}
