#include "config.h"
#include "chunk.h"

#include <stdlib.h>
#include "memory.h"

void chunk_init(Chunk* chunk) {
	chunk->count = 0;
	chunk->capacity = 0;
	chunk->code = NULL;
	chunk->lines = NULL;
	value_array_init(&chunk->constants);
}

void chunk_write(Chunk* chunk, uint8_t byte, unsigned line) {
	if (chunk->capacity < chunk->count + 1) {
		int oldCapacity = chunk->capacity;
		chunk->capacity = GROW_CAPACITY(oldCapacity);
		chunk->code = GROW_ARRAY(chunk->code, uint8_t, oldCapacity, chunk->capacity);
		chunk->lines = GROW_ARRAY(chunk->lines, unsigned, oldCapacity, chunk->capacity);
	}

	chunk->code[chunk->count] = byte;
	chunk->lines[chunk->count] = line;
	chunk->count++;
}

void chunk_free(Chunk* chunk) {
	FREE_ARRAY(uint8_t, chunk->code, chunk->capacity);
	FREE_ARRAY(unsigned, chunk->lines, chunk->capacity);
	value_array_free(&chunk->constants);
	chunk_init(chunk);
}

unsigned chunk_const_add(Chunk* chunk, Value value) {
	value_array_write(&chunk->constants, value);
	return chunk->constants.count - 1;
}