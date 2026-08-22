/*
 * Write a program to calculate electricity bill based on units consumed with these rates: 
 * First 100 units at ₹5/unit 
 * Next 100 units at ₹7/unit 
 * Next 100 units at ₹10/unit 
 * Above at ₹12/unit
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
    long long units, bill;
    if (!read_long_long(&units) || units < 0 || units > 1000000000000LL) {
        fprintf(stderr, "Enter units from 0 to 1000000000000.\n");
        return 1;
    }
    bill = (units < 100 ? units : 100) * 5;
    if (units > 100) bill += (units < 200 ? units - 100 : 100) * 7;
    if (units > 200) bill += (units < 300 ? units - 200 : 100) * 10;
    if (units > 300) bill += (units - 300) * 12;
    printf("Bill: Rs %lld\n", bill);
    return 0;
}
