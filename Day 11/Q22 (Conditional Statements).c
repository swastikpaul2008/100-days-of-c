/*
 * Write a program to find profit or loss percentage given cost price and selling price.
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
    double cost, selling;
    if (scanf("%lf %lf", &cost, &selling) != 2 ||
        !isfinite(cost) || !isfinite(selling) || cost < 0.0) {
        fprintf(stderr, "Enter finite prices and a non-negative cost price.\n");
        return 1;
    }
    if (cost == 0.0) {
        if (selling == 0.0) puts("No Profit No Loss");
        else puts("Profit percentage is undefined for zero cost.");
    } else if (selling > cost) {
        printf("Profit %.2f%%\n", (selling - cost) * 100.0 / cost);
    } else if (selling < cost) {
        printf("Loss %.2f%%\n", (cost - selling) * 100.0 / cost);
    } else {
        puts("No Profit No Loss");
    }
    return 0;
}
