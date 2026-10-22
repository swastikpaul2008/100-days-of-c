/*
 * Read a text file and count the total number of characters, words, and lines. A word is defined as a sequence of non-space characters separated by spaces or newlines.
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
    char filename[256];
    unsigned long long characters = 0, words = 0, lines = 0;
    int ch, in_word = 0;
    FILE *file;
    if (scanf("%255s", filename) != 1) { fprintf(stderr, "Expected a filename.\n"); return 1; }
    file = fopen(filename, "rb");
    if (file == NULL) { perror(filename); return 1; }
    while ((ch = fgetc(file)) != EOF) {
        ++characters;
        if (ch == '\n') ++lines;
        if (ch == ' ' || ch == '\n' || ch == '\r' || ch == '\t') in_word = 0;
        else if (!in_word) { ++words; in_word = 1; }
    }
    if (ferror(file)) { perror("Reading file"); fclose(file); return 1; }
    if (characters > 0 && fseek(file, -1L, SEEK_END) == 0 && fgetc(file) != '\n') ++lines;
    if (fclose(file) != 0) { perror("Closing file"); return 1; }
    printf("Characters=%llu, Words=%llu, Lines=%llu\n", characters, words, lines);
    return 0;
}
