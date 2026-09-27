/*
 * Check if one string is a rotation of another.
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
    char first[1002], second[1002];
    size_t length, other_length;
    if (fgets(first, sizeof(first), stdin) == NULL || fgets(second, sizeof(second), stdin) == NULL) {
        fprintf(stderr, "Expected two strings.\n"); return 1;
    }
    length = strcspn(first, "\n");
    other_length = strcspn(second, "\n");
    if (length != other_length) { puts("Not rotation"); return 0; }
    for (size_t shift = 0; shift < length; ++shift) {
        size_t i = 0;
        while (i < length && first[(shift + i) % (length == 0 ? 1 : length)] == second[i]) ++i;
        if (i == length) { puts("Rotation"); return 0; }
    }
    puts(length == 0 ? "Rotation" : "Not rotation");
    return 0;
}
