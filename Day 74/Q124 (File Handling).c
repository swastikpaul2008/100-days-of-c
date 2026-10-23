/*
 * Take two filenames from the user – a source file and a destination file. Copy all the content from the source file to the destination file using fgetc() and fputc().
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
    char source_name[256], destination_name[256];
    FILE *source, *destination;
    int ch, failed = 0;
    if (scanf("%255s %255s", source_name, destination_name) != 2) {
        fprintf(stderr, "Expected source and destination filenames.\n"); return 1;
    }
    source = fopen(source_name, "rb");
    if (source == NULL) { perror(source_name); return 1; }
    destination = fopen(destination_name, "wb");
    if (destination == NULL) { perror(destination_name); fclose(source); return 1; }
    while ((ch = fgetc(source)) != EOF)
        if (fputc(ch, destination) == EOF) { failed = 1; break; }
    if (ferror(source)) failed = 1;
    if (fclose(source) != 0) failed = 1;
    if (fclose(destination) != 0) failed = 1;
    if (failed) { fprintf(stderr, "File copy failed.\n"); return 1; }
    return 0;
}
