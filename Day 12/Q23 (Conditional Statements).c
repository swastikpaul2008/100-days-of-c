/*
 * Write a program to calculate library fine based on late days as follows: 
 * First 5 days late: ₹2/day 
 * Next 5 days late: ₹4/day 
 * Next 20 days days late: ₹6/day 
 * More than 30 days: Membership Cancelled.
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
    long long days, fine;
    if (!read_long_long(&days) || days < 0) {
        fprintf(stderr, "Enter a non-negative number of late days.\n");
        return 1;
    }
    if (days > 30) {
        puts("Membership Cancelled");
        return 0;
    }
    fine = (days < 5 ? days : 5) * 2;
    if (days > 5) fine += (days < 10 ? days - 5 : 5) * 4;
    if (days > 10) fine += (days - 10) * 6;
    printf("Fine Rs %lld\n", fine);
    return 0;
}
