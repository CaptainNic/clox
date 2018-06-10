#pragma once

#include "common.h"

typedef double Value;

typedef struct {
	unsigned capacity;
	unsigned count;
	Value* values;
} ValueArray;

void value_array_init(ValueArray* array);

void value_array_write(ValueArray* array, Value value);

void value_array_free(ValueArray* array);

/**
 * Prints the value.
 * TODO: Move this to debug code?
 */
void printValue(Value value);