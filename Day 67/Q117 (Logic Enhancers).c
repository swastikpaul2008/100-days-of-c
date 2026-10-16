/*
 * Write a program to take two sorted arrays of size m and n as input. Merge both the arrays such that the merged array is also sorted. Print the merged array.
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
    int first_count, second_count, first[500], second[500], i = 0, j = 0;
    if (scanf("%d", &first_count) != 1 || first_count < 0 || first_count > 500) { fprintf(stderr, "Invalid first array size.\n"); return 1; }
    for (int k = 0; k < first_count; ++k)
        if (scanf("%d", &first[k]) != 1 || (k > 0 && first[k] < first[k - 1])) { fprintf(stderr, "First array must be sorted.\n"); return 1; }
    if (scanf("%d", &second_count) != 1 || second_count < 0 || second_count > 500) { fprintf(stderr, "Invalid second array size.\n"); return 1; }
    for (int k = 0; k < second_count; ++k)
        if (scanf("%d", &second[k]) != 1 || (k > 0 && second[k] < second[k - 1])) { fprintf(stderr, "Second array must be sorted.\n"); return 1; }
    while (i < first_count || j < second_count) {
        int value;
        if (j == second_count || (i < first_count && first[i] <= second[j])) value = first[i++];
        else value = second[j++];
        printf("%s%d", (i + j) == 1 ? "" : " ", value);
    }
    putchar('\n');
    return 0;
}
