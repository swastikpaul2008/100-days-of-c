/*
 * Read a text file and count how many vowels and consonants are in the file. Ignore digits and special characters.
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
    unsigned long long vowels = 0, consonants = 0;
    int ch;
    FILE *file;
    if (scanf("%255s", filename) != 1) { fprintf(stderr, "Expected a filename.\n"); return 1; }
    file = fopen(filename, "r");
    if (file == NULL) { perror(filename); return 1; }
    while ((ch = fgetc(file)) != EOF) {
        if (isalpha((unsigned char)ch)) {
            int lower = tolower((unsigned char)ch);
            if (lower == 'a' || lower == 'e' || lower == 'i' || lower == 'o' || lower == 'u') ++vowels;
            else ++consonants;
        }
    }
    if (ferror(file)) { perror("Reading file"); fclose(file); return 1; }
    if (fclose(file) != 0) { perror("Closing file"); return 1; }
    printf("Vowels=%llu, Consonants=%llu\n", vowels, consonants);
    return 0;
}
