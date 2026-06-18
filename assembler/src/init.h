#include <fsl.h>

#ifndef __FSL_ASM__
typedef enum
{
    null_arch   = 0,
    x86         = 0x32,
    x86_64      = 0x64
} arch_t;

typedef enum {
    eax = 0xB8,
    ecx = 0xB9,
    edx = 0xBA,
    ebx = 0xBB,
    esp = 0xBC,
    ebp = 0xBD,
    esi = 0xBE,
    edi = 0xBF
} reg_t;

#define REG_COUNT 8
struct { u8 opcode; const string x86, string x64; } reg_info;
struct reg_info REGISTERS[REG_COUNT] = {
    { eax, "eax", "rax" },
    { ebx, "ebx", "rbx" },
    { ecx, "ecx", "rcx" },
    { edx, "edx", "rdx" },
    { ebp, "ebp", "rbp" },
    { esp, "esp", "rsp" },
    { edi, "edi", "rdi" },
    { esi, "esi", "rsi" }
};

typedef enum
{
    _no = 0,
    inc = 1,
    xor = 2,
    mov = 3,
    jmp = 4,
    syscall = 5,
    int_0x80 = 6,
    ret = 7
} INSTRUCTIONS;

/*
    Instruction Set Idenifiers

    TODO; is_instruction_set_valid(char *line)
*/
#define MAX_INSTRUCTIONS 4
struct instruction_set { INSTRUCTIONS in; string id; int args; };
struct instruction_set INSTRUCTION_SETS[] = {
    /* Enum Type - Raw String ID - Argument Per Instruction Set*/
    {inc,       "inc",      2},
    {jmp,       "jmp",      2},
    {xor,       "xor",      2},
    {mov,       "mov",      2},
    {syscall,   "syscall",  0},
    {int_0x80,  "int 0x80", 0},
    {ret,       "ret",      0}
};

/* EOS Idenifier (End Of String) for the .data section */
const u8 NULL_TERMINATOR = '\0';

/* .data section idenifier */
const u8 E_O_C[] = {0xFF, 0x00, 0xFF};

/*
    This goes after a string's length before the string in binary 
    Format Example: 
        0xFF 0x00 0xFF = SEPARATOR
        0xA2 - MEMORY SIZE
        0xFF - SEPARATOR
        ----String----
*/
const u8 BLACKSPACE = 0xFF;

/* Pre-set opcode */
#define SYSCALL     {0x0F, 0x05}
#define INI_0x80    {0xCD, 0x80}
#define RET         {0xC3}

#endif