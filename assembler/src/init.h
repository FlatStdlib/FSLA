#include <fsl.h>

#ifndef __FSL_ASM__

/* Target Arch, Register, Instruction Rules and Info */
typedef enum
{
    null_arch   = 0, x16 = 0x16, x86 = 0x32, x86_64 = 0x64
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
{ _no = 0, inc, xor, mov, jmp, syscall, int_0x80, ret } 
instruction_t;

/*
    Instruction Set Idenifiers

    TODO; is_instruction_set_valid(char *line)
*/
struct instruction_set {
    instruction_t in;
    string id;
    int args;
};

#define ARG_INSTRUCTIONS 4
#define TOTAL_INSTRUCTIONS 7
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

#define _SYSCALL     {0x0F, 0x05}
#define _INI_0x80    {0xCD, 0x80}
#define _RET         {0xC3}

typedef struct
{
	fd_t 	file;
	string 	filename;
	int 	filesize;
	string	content;

	u8		*opcode;
	i32		size;
	string  *buffers;
} _asmblr;

_asmblr init_assembler(string filename);
public fn parse_file(_asmblr *a);
public fn parse_instruction(_asmblr *a, string line);
public i64 get_instruction_info(_asmblr *a, string instruction);
#endif
