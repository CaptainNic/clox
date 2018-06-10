#include "config.h"
#include "debug.h"

#include <stdio.h>
#include "value.h"

static unsigned debug_inst_simple(const char* name, unsigned offset) {
	printf("%s\n", name);
	return offset + 1;
}

static unsigned debug_inst_constant(const char* name, Chunk* chunk, unsigned offset) {
	uint8_t constIdx = chunk->code[offset + 1];
	printf("%-16s 0x%02X '%g'\n", name, constIdx, chunk->constants.values[constIdx]);
	return offset + 2;
}

void dbg_chunk_disassemble(Chunk* chunk, const char* name) {
	printf("-- %s --\n", name);

	for (unsigned i = 0; i < chunk->count;) {
		i = dbg_instr_disassemble(chunk, i);
	}
}

unsigned dbg_instr_disassemble(Chunk* chunk, unsigned offset) {
	printf("%04d ", offset);
	if (offset > 0 && chunk->lines[offset] == chunk->lines[offset - 1]) {
		printf("   | ");
	} else {
		printf("%4d ", chunk->lines[offset]);
	}

	uint8_t instruction = chunk->code[offset];
	switch (instruction) {
	case OP_CONSTANT:
		return debug_inst_constant("OP_CONSTANT", chunk, offset);
	case OP_RETURN:
		return debug_inst_simple("OP_RETURN", offset);
	default:
		printf("Unknown opcode %d\n", instruction);
		return offset + 1;
	}
}

void dbg_stack_dump(VM* vm) {
	printf("(%d) ", vm->stackTop - vm->stack);
	for (Value* slot = vm->stack; slot < vm->stackTop; ++slot) {
		printf("[%g]", *slot);
	}
	printf("\n");
}
