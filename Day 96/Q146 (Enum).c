/*
 * Create Employee structure with nested Date structure for joining date and print details.
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
    struct Date { int day, month, year; };
    struct Employee { char name[100]; int id; struct Date joined; } employee;
    if (scanf("%99s %d %d %d %d", employee.name, &employee.id,
              &employee.joined.day, &employee.joined.month, &employee.joined.year) != 5 ||
        employee.id < 0 || employee.joined.day < 1 || employee.joined.day > 31 ||
        employee.joined.month < 1 || employee.joined.month > 12 || employee.joined.year < 1) {
        fprintf(stderr, "Invalid employee or joining date.\n"); return 1;
    }
    printf("%s %d %02d/%02d/%04d\n", employee.name, employee.id,
           employee.joined.day, employee.joined.month, employee.joined.year);
    return 0;
}
