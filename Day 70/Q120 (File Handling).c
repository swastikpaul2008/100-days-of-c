/*
 * Write a program to take a string input. Change it to sentence case.
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
    char text[1002];
    int start_of_word = 1;
    if (fgets(text, sizeof(text), stdin) == NULL) { fprintf(stderr, "Expected a line of text.\n"); return 1; }
    for (size_t i = 0; text[i] != '\0' && text[i] != '\n'; ++i) {
        unsigned char ch = (unsigned char)text[i];
        if (isspace(ch)) start_of_word = 1;
        else {
            text[i] = (char)(start_of_word ? toupper(ch) : tolower(ch));
            start_of_word = 0;
        }
    }
    fputs(text, stdout);
    if (strchr(text, '\n') == NULL) putchar('\n');
    return 0;
}
