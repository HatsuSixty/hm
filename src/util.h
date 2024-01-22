#ifndef UTIL_H_
#define UTIL_H_

#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char* read_entire_file(const char* file_path, size_t* count);
void free_entire_file(char* buffer);

#endif  // UTIL_H_
