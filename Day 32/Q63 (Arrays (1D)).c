/*
 * Merge two arrays.
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
    int first_count, second_count, first[500], second[500];
    if (scanf("%d", &first_count) != 1 || first_count < 0 || first_count > 500) { fprintf(stderr, "Invalid first array size.\n"); return 1; }
    for (int i = 0; i < first_count; ++i)
        if (scanf("%d", &first[i]) != 1) { fprintf(stderr, "Invalid first array.\n"); return 1; }
    if (scanf("%d", &second_count) != 1 || second_count < 0 || second_count > 500) { fprintf(stderr, "Invalid second array size.\n"); return 1; }
    for (int i = 0; i < second_count; ++i)
        if (scanf("%d", &second[i]) != 1) { fprintf(stderr, "Invalid second array.\n"); return 1; }
    for (int i = 0; i < first_count; ++i) printf("%s%d", i == 0 ? "" : " ", first[i]);
    for (int i = 0; i < second_count; ++i) printf("%s%d", first_count + i == 0 ? "" : " ", second[i]);
    putchar('\n');
    return 0;
}
