#include <fsl.h>

#ifndef __NEXA_OPCODE_LIB__

/* Target Arch, Register, Instruction Rules and Info */
typedef enum
{
    null_arch = 0,
    x8 = 0x8,
    x16 = 0x16, 
    x86 = 0x32, 
    x86_64 = 0x64
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

struct _reg {
    u8 opcode;
    const string x86;
    const string x64;
};

#define REG_COUNT 8
extern struct _reg _REGISTERS[];

typedef enum
{ _no = 0, inc, _int, xor, nop, mov, lea, jmp, syscall, int_0x80, ret } 
instruction_t;


typedef u8 *(*asm_gen_handler)(reg_t reg, string q, arch_t arch);
/*
    Instruction Set Idenifiers

    TODO; is_instruction_set_valid(char *line)
*/
struct instruction_set {
    instruction_t in;
    string id;
    int args;
    void *handler;
};

#define ARG_INSTRUCTIONS 4
#define TOTAL_INSTRUCTIONS 8
extern struct instruction_set INSTRUCTION_SETS[];
typedef struct instruction_set _iset;

//
// Pre-set opcode 
//

/* EOS Idenifier (End Of String) for the .data section */
extern const u8 NULL_TERMINATOR;

/* .data section idenifier */
extern const u8 E_O_C[];

/*
    This goes after a string's length before the string in binary 
    Format Example: 
        0xFF 0x00 0xFF = SEPARATOR
        0xA2 - MEMORY SIZE
        0xFF - SEPARATOR
        ----String----
*/
extern const u8 BLACKSPACE;

/* instructions.c */

public ptr parse_instruction(string line, arch_t arch);
public u8 *syscall_gen();
public u8 *int_0x80_gen();
public asm_gen_handler mov_gen(reg_t reg, string q, arch_t arch);
public asm_gen_handler lea_gen(reg_t reg, string q, arch_t arch);

/* db.c */
public reg_t reg_to_type(string reg);
public i64 get_instruction_info(string instruction);
public instruction_t checknget_instruction(string q, string dest);

/* utils.c */
public u64 validate_integer(string val);
u8 hex_value(char c);

#endif