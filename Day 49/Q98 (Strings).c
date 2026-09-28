/*
 * Print initials of a name with the surname displayed in full.
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
    char name[1002], *words[100], *word;
    int count = 0;
    if (fgets(name, sizeof(name), stdin) == NULL) { fprintf(stderr, "Expected a name.\n"); return 1; }
    word = strtok(name, " \t\r\n");
    while (word != NULL && count < 100) { words[count++] = word; word = strtok(NULL, " \t\r\n"); }
    if (word != NULL || count < 2) { fprintf(stderr, "Enter a name with at least two words (up to 100).\n"); return 1; }
    for (int i = 0; i < count - 1; ++i) printf("%c.", (char)toupper((unsigned char)words[i][0]));
    printf(" %s\n", words[count - 1]);
    return 0;
}
