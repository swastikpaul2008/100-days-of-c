/*
 * Open an existing file in append mode and allow the user to enter a new line of text. Append the text at the end without overwriting existing content.
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
    char filename[256], line[1002];
    FILE *file;
    if (fgets(filename, sizeof(filename), stdin) == NULL) { fprintf(stderr, "Expected a filename.\n"); return 1; }
    filename[strcspn(filename, "\r\n")] = '\0';
    if (filename[0] == '\0' || fgets(line, sizeof(line), stdin) == NULL) { fprintf(stderr, "Expected filename and text line.\n"); return 1; }
    line[strcspn(line, "\r\n")] = '\0';
    file = fopen(filename, "a");
    if (file == NULL) { perror(filename); return 1; }
    {
        int write_failed = fprintf(file, "%s\n", line) < 0;
        int close_failed = fclose(file) != 0;
        if (write_failed || close_failed) { perror("Appending file"); return 1; }
    }
    return 0;
}
