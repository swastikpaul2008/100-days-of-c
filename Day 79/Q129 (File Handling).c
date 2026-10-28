/*
 * A file numbers.txt contains a list of integers separated by spaces. Read all integers, compute their sum and average, and print both.
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
    FILE *file = fopen("numbers.txt", "r");
    long long value, sum = 0;
    unsigned long long count = 0;
    char token[128];
    if (file == NULL) { perror("numbers.txt"); return 1; }
    while (fscanf(file, "%127s", token) == 1) {
        if (!parse_long_long(token, &value)) {
            fprintf(stderr, "numbers.txt contains an invalid integer.\n");
            fclose(file);
            return 1;
        }
        if ((value > 0 && sum > LLONG_MAX - value) ||
            (value < 0 && sum < LLONG_MIN - value)) {
            fprintf(stderr, "Sum exceeds the supported range.\n"); fclose(file); return 1;
        }
        sum += value;
        ++count;
    }
    if (ferror(file)) { perror("Reading numbers.txt"); fclose(file); return 1; }
    if (fclose(file) != 0) { perror("Closing numbers.txt"); return 1; }
    if (count == 0) { fprintf(stderr, "numbers.txt contains no integers.\n"); return 1; }
    printf("Sum=%lld, Average=%.2f\n", sum, (double)sum / (double)count);
    return 0;
}
