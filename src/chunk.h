#pragma once

#include "common.h"
#include "value.h"

typedef enum {
	OP_CONSTANT,	// [ opcode8, constant_index8 ]
	OP_ADD,			// [ opcode8 ]
	OP_SUBTRACT,	// [ opcode8 ]
	OP_MULTIPLY,	// [ opcode8 ]
	OP_DIVIDE,		// [ opcode8 ]
	OP_NEGATE,		// [ opcode8 ]
	OP_RETURN		// [ opcode8 ]
} OpCode;

typedef struct {
	unsigned count;
	unsigned capacity;
	uint8_t* code;
	unsigned* lines;
	ValueArray constants;
} Chunk;

/**
 * Initializes a chunk.
 * - Chunk* chunk: the chunk to initialize.
 */
void chunk_init(Chunk* chunk);

/**
 * Writes a byte to the chunk's code section.
 * - Chunk* chunk: the chunk to write to.
 * - uint8_t byte: the code to write
 * - unsigned line: the line number
 */
void chunk_write(Chunk* chunk, uint8_t byte, unsigned line);

/**
 * Frees a chunk and reinitializes it.
 * - Chunk* chunk: the chunk to free.
 */
void chunk_free(Chunk* chunk);

/**
 * Adds a constant to the Chunk.
 *  - Chunk* chunk: the chunk to add the constant to
 *  - Value value: the value of the constant
 * Returns: the index of the added constant.
 */
unsigned chunk_const_add(Chunk* chunk, Value value);