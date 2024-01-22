#include "util.h"

#include <stddef.h>

char* read_entire_file(const char* file_path, size_t* count)
{
    FILE* file = fopen(file_path, "r");

    if (file == NULL) {
        fprintf(stderr, "ERROR: could open file `%s`: %s\n", file_path,
                strerror(errno));
        exit(1);
    }

    if (fseek(file, 0L, SEEK_END) != 0) {
        fprintf(stderr, "ERROR: could not seek to the end of `%s`: %s",
                file_path, strerror(errno));
        exit(1);
    }

    long bufsize = ftell(file);
    if (bufsize < 0) {
        fprintf(stderr,
                "ERROR: could not get current position of stream `%s`: %s",
                file_path, strerror(errno));
        exit(1);
    }

    char* source = malloc(sizeof(char) * bufsize + 1);

    if (fseek(file, 0L, SEEK_SET) != 0) {
        fprintf(stderr, "ERROR: could not seek to the beginning of `%s`: %s\n",
                file_path, strerror(errno));
        exit(1);
    }

    size_t new_size = fread((void*)source, sizeof(char), bufsize, file);

    if (ferror(file)) {
        fprintf(stderr, "ERROR: error reading file `%s`: %s\n", file_path,
                strerror(errno));
        exit(1);
    }

    source[new_size++] = '\0';

    fclose(file);

    if (count) *count = new_size;
    return source;
}

void free_entire_file(char* buffer) { free(buffer); }
