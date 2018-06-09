#pragma once

#include "chunk.h"

void dbg_chunk_disassemble(Chunk* chunk, const char* name);

unsigned dbg_instr_disassemble(Chunk* chunk, unsigned i);
