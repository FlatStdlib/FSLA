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

struct instruction_set INSTRUCTION_SETS[] = {
    /* Enum Type - Raw String ID - Argument Per Instruction Set */
    {inc,       "inc",      2},
    {jmp,       "jmp",      2},
    {xor,       "xor",      2},
    {mov,       "mov",      2},
    {syscall,   "syscall",  0},
    {int_0x80,  "int 0x80", 0},
    {ret,       "ret",      0}
};

const u8 NULL_TERMINATOR = '\0';
const u8 E_O_C[] = {0xFF, 0x00, 0xFF};
const u8 BLACKSPACE = 0xFF;