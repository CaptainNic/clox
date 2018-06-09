#include "common.h"
#include "debug.h"
#include "vm.h"

#include "chunk.h"

int main(int argc, const char* argv[]) {
	VM vm;

	vm_init(&vm);

	Chunk chunk;
	chunk_init(&chunk);
	chunk_write(&chunk, OP_CONSTANT, 1);
	// Loss of precision here when assigning constant offset
	// means we have an implied maximum of 256 constants per chunk.
	chunk_write(&chunk, (uint8_t)chunk_const_add(&chunk, 1), 1);
	chunk_write(&chunk, OP_RETURN, 1);
	
	vm_interpret(&vm, &chunk);

	vm_free(&vm);
	chunk_free(&chunk);

	return 0;
}