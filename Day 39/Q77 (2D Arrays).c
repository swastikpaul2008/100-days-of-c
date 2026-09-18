/*
 * Check if the elements on the diagonal of a matrix are distinct.
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
    int size, columns, matrix[50][50], distinct = 1;
    if (scanf("%d %d", &size, &columns) != 2 || size < 1 || size > 50 || columns != size) {
        fprintf(stderr, "A square matrix up to 50 by 50 is required.\n"); return 1;
    }
    for (int row = 0; row < size; ++row)
        for (int col = 0; col < size; ++col)
            if (scanf("%d", &matrix[row][col]) != 1) { fprintf(stderr, "Invalid matrix input.\n"); return 1; }
    for (int i = 0; i < size; ++i)
        for (int j = i + 1; j < size; ++j)
            if (matrix[i][i] == matrix[j][j]) distinct = 0;
    puts(distinct ? "True" : "False");
    return 0;
}
