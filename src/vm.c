#include "vm.h"

#include <errno.h>
#include <stdio.h>
#include <string.h>

#include "util.h"

void stack_push(Stack* stack, Stack_Item item)
{
    if (stack->count > STACK_CAPACITY) {
        fprintf(stderr, "%s:%d: ERROR: Stack overflow\n", __FILE__, __LINE__);
        exit(1);
    }

    stack->items[stack->count++] = item;
}

Stack_Item stack_pop(Stack* stack)
{
    if ((int32_t)stack->count < 0) {
        fprintf(stderr, "%s:%d: ERROR: Stack underflow\n", __FILE__, __LINE__);
        exit(1);
    }

    return stack->items[--stack->count];
}

HM* hm_new(void) { return malloc(sizeof(HM)); }
void hm_reset(HM* hm) { *hm = (HM){0}; }
void hm_free(HM* hm) { free(hm); }

void hm_execute_bytecode(HM* hm, HM_Inst* instructions, size_t inst_count)
{
    for (size_t i = 0; i < inst_count; ++i) {
        HM_Inst inst = instructions[i];
        switch (inst.type) {
            case INST_PUSH_I32:
                stack_push(&hm->stack, inst.operand.int32);
                break;
            case INST_PLUS_I32: {
                int32_t b = stack_pop(&hm->stack);
                int32_t a = stack_pop(&hm->stack);
                stack_push(&hm->stack, (int32_t)a + b);
            } break;
            case INST_PRINT:
                printf("%ld\n", stack_pop(&hm->stack));
                break;
        }
    }
}

void hm_save_program(const char* file_path, HM_Inst* instructions,
                     size_t inst_count)
{
    FILE* file = fopen(file_path, "w");
    if (file == NULL) {
        fprintf(stderr, "ERROR: could not open file `%s`: %s\n", file_path,
                strerror(errno));
        exit(1);
    }

    fwrite(instructions, sizeof(HM_Inst), inst_count, file);
    if (ferror(file) != 0) {
        fprintf(stderr, "ERROR: could not write to file `%s`: %s\n", file_path,
                strerror(errno));
        exit(1);
    }

    fclose(file);
}

size_t hm_load_program(const char* file_path, HM_Inst* instructions)
{
    size_t size = 0;
    char* source = read_entire_file(file_path, &size);
    size -= 1;
    memcpy(instructions, source, size);
    return size / sizeof(HM_Inst);
}
