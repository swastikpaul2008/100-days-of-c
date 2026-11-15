/*
 * Store employee data in a binary file using fwrite() and read using fread().
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
    struct Employee { int id; char name[100]; double salary; } employee, loaded;
    FILE *file;
    if (scanf("%d %99s %lf", &employee.id, employee.name, &employee.salary) != 3 ||
        employee.id < 0 || !isfinite(employee.salary) || employee.salary < 0.0) {
        fprintf(stderr, "Invalid employee record.\n"); return 1;
    }
    file = fopen("employee.dat", "wb");
    if (file == NULL) { perror("employee.dat"); return 1; }
    {
        int write_failed = fwrite(&employee, sizeof(employee), 1, file) != 1;
        int close_failed = fclose(file) != 0;
        if (write_failed || close_failed) {
        perror("Writing employee.dat"); return 1;
        }
    }
    file = fopen("employee.dat", "rb");
    if (file == NULL) { perror("employee.dat"); return 1; }
    {
        int read_failed = fread(&loaded, sizeof(loaded), 1, file) != 1;
        int close_failed = fclose(file) != 0;
        if (read_failed || close_failed) {
        perror("Reading employee.dat"); return 1;
        }
    }
    printf("%d %s %.2f\n", loaded.id, loaded.name, loaded.salary);
    return 0;
}
