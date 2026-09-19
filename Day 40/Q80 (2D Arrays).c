/*
 * Multiply two matrices.
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
    int rows, common, other_rows, columns, left[50][50], right[50][50];
    if (scanf("%d %d", &rows, &common) != 2 || rows < 1 || rows > 50 || common < 1 || common > 50) {
        fprintf(stderr, "Invalid first matrix dimensions.\n"); return 1;
    }
    for (int row = 0; row < rows; ++row)
        for (int col = 0; col < common; ++col)
            if (scanf("%d", &left[row][col]) != 1) { fprintf(stderr, "Invalid first matrix.\n"); return 1; }
    if (scanf("%d %d", &other_rows, &columns) != 2 || other_rows != common ||
        columns < 1 || columns > 50) { fprintf(stderr, "Incompatible second matrix dimensions.\n"); return 1; }
    for (int row = 0; row < other_rows; ++row)
        for (int col = 0; col < columns; ++col)
            if (scanf("%d", &right[row][col]) != 1) { fprintf(stderr, "Invalid second matrix.\n"); return 1; }
    for (int row = 0; row < rows; ++row) {
        for (int col = 0; col < columns; ++col) {
            long long sum = 0;
            for (int index = 0; index < common; ++index)
                sum += (long long)left[row][index] * right[index][col];
            printf("%s%lld", col == 0 ? "" : " ", sum);
        }
        putchar('\n');
    }
    return 0;
}
