#include <stdint.h>
#include <stdio.h>

#include "vm.h"

void create_program(const char* file_path)
{
    HM_Inst instructions[] = {
        (HM_Inst){.type = INST_PUSH_I32, .operand = {34}},
        (HM_Inst){.type = INST_PUSH_I32, .operand = {35}},
        (HM_Inst){.type = INST_PLUS_I32},
        (HM_Inst){.type = INST_PRINT},
        (HM_Inst){.type = INST_PUSH_I32, .operand = {400}},
        (HM_Inst){.type = INST_PUSH_I32, .operand = {20}},
        (HM_Inst){.type = INST_PLUS_I32},
        (HM_Inst){.type = INST_PRINT},
    };

    hm_save_program(file_path, instructions,
                    sizeof(instructions) / sizeof(instructions[0]));
}

int main(void)
{
    create_program("foo.hm");
    // Enough for our example
    HM_Inst instructions[20] = {0};
    size_t inst_count = hm_load_program("foo.hm", instructions);

    HM* hm = hm_new();
    hm_execute_bytecode(hm, instructions, inst_count);
    hm_free(hm);

    return 0;
}
