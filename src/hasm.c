#include <ctype.h>
#include <errno.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "util.h"

#define TODO printf("%s:%d: TODO: Not implemented yet\n", __FILE__, __LINE__)

typedef struct {
    const char* file_path;
    size_t row;
} Location;
#define LOC(loc) loc.file_path, loc.row

typedef enum {
    TOKEN_INT,
    TOKEN_SYM,
} Token_Type;

typedef union {
    const char* string;
    uint64_t integer;
} Token_Value;

typedef struct {
    Token_Type type;
    Token_Value value;
    Location loc;
} Token;

size_t lexer_lex_string(const char* file_path, const char* s, Token* tokens)
{
    size_t string_len = strlen(s) + 1;

    // is this a very hacky workaround? yes
    // do i care? no
    char* string = (char*)malloc(sizeof(char) * string_len);
    memcpy(string, s, string_len - 1);
    string[string_len - 1] = ' ';

    char string_buffer[string_len];
    size_t string_buffer_len = 0;
    memset(string_buffer, 0, string_len);

    Location loc = {
        .file_path = file_path,
        .row = 1,
    };

    size_t token_count = 0;

    for (size_t i = 0; i < string_len; ++i) {
        if (isspace(string[i])) {
            Location token_loc = loc;

            if (string[i] == '\n') {
                ++loc.row;
                ++i;
            }

            char* endptr;
            long long token_ll = strtoll(string_buffer, &endptr, 10);

            if (*endptr == '\0') {
                tokens[token_count++] = (Token){
                    .type = TOKEN_INT,
                    .value = {.integer = token_ll},
                    .loc = token_loc,
                };
            }
            else {
                Token token = {0};
                token.type = TOKEN_SYM;
                size_t bufsize = sizeof(char) * string_buffer_len + 1;
                token.value.string = (char*)malloc(bufsize);
                memset((void*)token.value.string, 0, bufsize);
                memcpy((void*)token.value.string, string_buffer,
                       string_buffer_len);
                token.loc = token_loc;
                tokens[token_count++] = token;
            }

            string_buffer_len = 0;
            memset(string_buffer, 0, string_len);

            while (isspace(string[i])) {
                if (string[i] == '\n') ++loc.row;
                ++i;
            };
            --i;
        }
        else {
            string_buffer[string_buffer_len++] = string[i];
        }
    }
    free((void*)string);

    return token_count;
}

size_t lexer_lex_file(const char* file_path, Token* tokens)
{
    char* source = read_entire_file(file_path, NULL);
    size_t token_count = lexer_lex_string(file_path, source, tokens);
    free_entire_file(source);

    return token_count;
}

void lexer_print_tokens(Token* tokens, size_t token_count)
{
    for (size_t i = 0; i < token_count; ++i) {
        printf("-----------\n");
        Token token = tokens[i];
        printf("%s:%ld: Token %ld:\n", LOC(token.loc), i);
        printf("Token Type: %d\n", token.type);
        if (token.type == TOKEN_INT) {
            printf("Token Value: %ld\n", token.value.integer);
        }
        else {
            printf("Token Value: %s\n", token.value.string);
        }
    }
}

void lexer_free_tokens(Token* tokens, size_t token_count)
{
    for (size_t i = 0; i < token_count; ++i) {
        Token token = tokens[i];
        if (token.type == TOKEN_SYM) {
            free((void*)token.value.string);
        }
    }
}

int main(void)
{
    Token* tokens = (Token*)malloc(sizeof(Token) * 640000);

    size_t token_count = lexer_lex_file("foo.hasm", tokens);
    lexer_print_tokens(tokens, token_count);
    lexer_free_tokens(tokens, token_count);

    free(tokens);
    return 0;
}
