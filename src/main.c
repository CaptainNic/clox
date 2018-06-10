#include "config.h"

#include "common.h"
#include "chunk.h"
#include "debug.h"
#include "vm.h"

int main(int argc, const char* argv[]) {
	VM vm;

	vm_init(&vm);

	Chunk chunk;
	chunk_init(&chunk);
	chunk_write(&chunk, OP_CONSTANT, 1);
	// Loss of precision here when assigning constant offset
	// means we have an implied maximum of 256 constants per chunk.
	chunk_write(&chunk, (uint8_t)chunk_const_add(&chunk, 2), 1);

	chunk_write(&chunk, OP_CONSTANT, 1);
	chunk_write(&chunk, (uint8_t)chunk_const_add(&chunk, 5), 1);

	chunk_write(&chunk, OP_CONSTANT, 1);
	chunk_write(&chunk, (uint8_t)chunk_const_add(&chunk, 1.2), 1);

	chunk_write(&chunk, OP_CONSTANT, 1);
	chunk_write(&chunk, (uint8_t)chunk_const_add(&chunk, 2.3), 1);

	chunk_write(&chunk, OP_ADD, 1);
	
	chunk_write(&chunk, OP_MULTIPLY, 1);
	
	chunk_write(&chunk, OP_DIVIDE, 1);

	chunk_write(&chunk, OP_NEGATE, 2);
	chunk_write(&chunk, OP_RETURN, 2);
	
	vm_interpret(&vm, &chunk);

	vm_free(&vm);
	chunk_free(&chunk);

	return 0;
}