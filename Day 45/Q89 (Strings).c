/*
 * Count frequency of a given character in a string.
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
    char text[1002], input[32], target;
    size_t length;
    if (fgets(text, sizeof(text), stdin) == NULL || fgets(input, sizeof(input), stdin) == NULL) {
        fprintf(stderr, "Expected a string and a character.\n"); return 1;
    }
    length = strcspn(text, "\n");
    if (input[0] == '\0' || input[0] == '\n') { fprintf(stderr, "Expected a character.\n"); return 1; }
    target = input[0];
    {
        size_t count = 0;
        for (size_t i = 0; i < length; ++i) if (text[i] == target) ++count;
        printf("%zu\n", count);
    }
    return 0;
}
