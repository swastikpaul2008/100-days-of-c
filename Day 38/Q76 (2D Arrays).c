/*
 * Check if a matrix is symmetric.
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
    int rows, columns, matrix[50][50], symmetric = 1;
    if (scanf("%d %d", &rows, &columns) != 2 || rows < 1 || rows > 50 ||
        columns != rows) { fprintf(stderr, "A square matrix up to 50 by 50 is required.\n"); return 1; }
    for (int row = 0; row < rows; ++row)
        for (int col = 0; col < columns; ++col)
            if (scanf("%d", &matrix[row][col]) != 1) { fprintf(stderr, "Invalid matrix input.\n"); return 1; }
    for (int row = 0; row < rows; ++row)
        for (int col = row + 1; col < columns; ++col)
            if (matrix[row][col] != matrix[col][row]) symmetric = 0;
    puts(symmetric ? "True" : "False");
    return 0;
}
