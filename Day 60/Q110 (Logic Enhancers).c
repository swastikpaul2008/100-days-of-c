/*
 * Write a program to take an integer array arr and an integer k as inputs. The task is to find the maximum element in each subarray of size k moving from left to right. Print the maximum elements for each window separated by spaces as output.
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
    int n, window, values[1000];
    if (scanf("%d", &n) != 1 || n < 1 || n > 1000) { fprintf(stderr, "Invalid array size.\n"); return 1; }
    for (int i = 0; i < n; ++i) if (scanf("%d", &values[i]) != 1) { fprintf(stderr, "Invalid array.\n"); return 1; }
    if (scanf("%d", &window) != 1 || window < 1 || window > n) { fprintf(stderr, "Window must be from 1 to array size.\n"); return 1; }
    for (int start = 0; start + window <= n; ++start) {
        int maximum = values[start];
        for (int i = start + 1; i < start + window; ++i) if (values[i] > maximum) maximum = values[i];
        printf("%s%d", start == 0 ? "" : " ", maximum);
    }
    putchar('\n');
    return 0;
}
