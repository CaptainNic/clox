#pragma once

#include "common.h"

#define GROW_CAPACITY(capacity) \
	((capacity) < 8 ? 8 : (capacity) * 2)

#define GROW_ARRAY(prev, type, oldCount, count) \
	(type*)reallocate(prev, sizeof(type) * (oldCount), sizeof(type) * (count))

#define FREE_ARRAY(type, arr, count) \
	reallocate(arr, sizeof(type) * (count), 0);

void* reallocate(void* prev, size_t oldSize, size_t newSize);