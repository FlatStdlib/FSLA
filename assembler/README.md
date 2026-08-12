<div align="center">
    <h1>Nexa Lang</h1>
    <p>A C-like language w/ built-in a assembler for assembly macros</p>
</div>

# Compilation Pipeline

Nexa -> AST -> Instruction Encoding

# Features

Note that the items listed below are linked to the parser of such parts
- [Variables](https://github.com/FlatStdlib/FSLA/blob/main/assembler/src/nexa/variable.c)
- [Functions](https://github.com/FlatStdlib/FSLA/blob/main/assembler/src/nexa/function.c)
- [Structs](https://github.com/FlatStdlib/FSLA/blob/main/assembler/src/nexa/struct.c)
- [Variable Modification](https://github.com/FlatStdlib/FSLA/blob/cceb0220285396ce8c3de627e6f5d0d2b9c688ff/assembler/src/nexa/function.c#L113)
- [Function Calls](https://github.com/FlatStdlib/FSLA/blob/cceb0220285396ce8c3de627e6f5d0d2b9c688ff/assembler/src/nexa/function.c#L113)

# File Structure

```
| - Nexa Compiler & Assembler
|
| - main.c 						// Nexa programming language
| - src/						// Source Code
	| - init.c					// Initialization and Start Of Parser
	| - init.h
	| - nexa/					// Parsers, Validators, & Checks
		| - function.c			// Function Parsers
		| - parser.c			// Token Parsers & Checks
		| - struct.c			// Struct Parsers
		| - types.c				// Type Arrays && Sizes 
		| - types.h				// Built-in Type Declaration
		| - variable.c			// Variable Parsers
		| - assembler/			// Assembler
			| - db.c			// Registers, Encoded Byte(s) Declaration
			| - instructions.c	// Operand-Based Instruction to Encoded Byte(s) Gen
			| - opcode.h		// Arch, Instruction(s), and Register(s) Declaration
			| - utils.c			// Dynamic List Lookup
| - tests/
