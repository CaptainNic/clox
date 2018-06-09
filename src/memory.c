#include <stdlib.h>
#include "common.h"

#include "memory.h"

void* reallocate(void* prev, size_t oldSize, size_t newSize) {
	if (!newSize) {
		free(prev);
		return NULL;
	}

	return realloc(prev, newSize);
}