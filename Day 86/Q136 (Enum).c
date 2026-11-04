/*
 * Use enum to represent menu choices (ADD, SUBTRACT, MULTIPLY) and perform operations using switch.
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
    enum Operation { ADD = 1, SUBTRACT, MULTIPLY };
    int choice;
    int left, right;
    if (scanf("%d %d %d", &choice, &left, &right) != 3 ||
        choice < ADD || choice > MULTIPLY) { fprintf(stderr, "Enter operation 1..3 and two integers.\n"); return 1; }
    switch ((enum Operation)choice) {
        case ADD: printf("%lld\n", (long long)left + right); break;
        case SUBTRACT: printf("%lld\n", (long long)left - right); break;
        case MULTIPLY: printf("%lld\n", (long long)left * right); break;
    }
    return 0;
}
