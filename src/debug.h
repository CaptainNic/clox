#pragma once

#include "chunk.h"
#include "vm.h"

void dbg_chunk_disassemble(Chunk* chunk, const char* name);

unsigned dbg_instr_disassemble(Chunk* chunk, unsigned i);

void dbg_stack_dump(VM* vm);
