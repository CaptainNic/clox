#pragma once

#include "common.h"

typedef double Value;

typedef struct {
	unsigned capacity;
	unsigned count;
	Value* values;
} ValueArray;

void initValueArray(ValueArray* array);

void writeValueArray(ValueArray* array, Value value);

void freeValueArray(ValueArray* array);

/**
 * Prints the value.
 * TODO: Move this to debug code?
 */
void printValue(Value value);