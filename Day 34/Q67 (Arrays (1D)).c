/*
 * Insert an element in an array at a given position.
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
    int n, position, item, values[1001];
    if (scanf("%d", &n) != 1 || n < 0 || n >= 1000) { fprintf(stderr, "Invalid array size.\n"); return 1; }
    for (int i = 0; i < n; ++i)
        if (scanf("%d", &values[i]) != 1) { fprintf(stderr, "Invalid array input.\n"); return 1; }
    if (scanf("%d %d", &position, &item) != 2 || position < 0 || position > n) {
        fprintf(stderr, "Position must be from 0 to %d.\n", n); return 1;
    }
    for (int i = n; i > position; --i) values[i] = values[i - 1];
    values[position] = item;
    for (int i = 0; i <= n; ++i) printf("%s%d", i == 0 ? "" : " ", values[i]);
    putchar('\n');
    return 0;
}
