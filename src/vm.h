#ifndef VM_H_
#define VM_H_

#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

typedef enum {
    INST_PUSH_I32,
    INST_PLUS_I32,
    INST_PRINT,
} HM_Inst_Type;

typedef union {
    int32_t int32;
} HM_Inst_Operand;

typedef struct {
    HM_Inst_Type type;
    HM_Inst_Operand operand;
} HM_Inst;

typedef uint64_t Stack_Item;

#define STACK_CAPACITY 640000
typedef struct {
    Stack_Item items[STACK_CAPACITY];
    size_t count;
} Stack;

typedef struct {
    Stack stack;
} HM;

HM* hm_new(void);
void hm_reset(HM* hm);
void hm_free(HM* hm);
void hm_execute_bytecode(HM* hm, HM_Inst* instructions, size_t inst_count);
void hm_save_program(const char* file_path, HM_Inst* instructions,
                     size_t inst_count);
size_t hm_load_program(const char* file_path, HM_Inst* instructions);
void stack_push(Stack* stack, Stack_Item item);
Stack_Item stack_pop(Stack* stack);

#endif  // VM_H_
