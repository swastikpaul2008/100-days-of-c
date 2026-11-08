/*
 * Define a struct with enum Gender and print person's gender.
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
    enum Gender { FEMALE = 1, MALE, OTHER };
    struct Person { char name[100]; enum Gender gender; } person;
    int gender;
    static const char *names[] = {"", "Female", "Male", "Other"};
    if (scanf("%99s %d", person.name, &gender) != 2 || gender < FEMALE || gender > OTHER) {
        fprintf(stderr, "Enter a name and gender code 1..3.\n"); return 1;
    }
    person.gender = (enum Gender)gender;
    printf("%s: %s\n", person.name, names[person.gender]);
    return 0;
}
