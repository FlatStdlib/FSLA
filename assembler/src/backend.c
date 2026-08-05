#include "init.h"

struct _reg _REGISTERS[] = {
    { eax, "eax", "rax" },
    { ebx, "ebx", "rbx" },
    { ecx, "ecx", "rcx" },
    { edx, "edx", "rdx" },
    { ebp, "ebp", "rbp" },
    { esp, "esp", "rsp" },
    { edi, "edi", "rdi" },
    { esi, "esi", "rsi" }
};

/*
        TYPE | IDENIFIER | OPERANDS Fillment
*/
struct instruction_set INSTRUCTION_SETS[] = {
    {inc,       "inc",      1},
    {jmp,       "jmp",      1},
    {xor,       "xor",      2},
    {mov,       "mov",      2, mov_gen},
    {_int,      "int",      1},
    {syscall,   "syscall",  0},
    {ret,       "ret",      0}
};

const u8 NULL_TERMINATOR = '\0';
const u8 E_O_C[] = {0xFF, 0x00, 0xFF};
const u8 BLACKSPACE = 0xFF;