#pragma once

#include "chunk.h"
#include "value.h"

#define STACK_MAX 256

typedef struct {
    Chunk* chunk;
    uint8_t* ip;
    Value stack[STACK_MAX];
    Value* stackTop;
} VM;

typedef enum {
    INTERPRET_OK,
    INTERPRET_COMPILE_ERROR,
    INTERPRET_RUNTIME_ERROR
} InterpretResult;

void vm_init(VM* vm);

void vm_free(VM* vm);

InterpretResult vm_interpret(VM* vm, const char* source);

void vm_stack_push(VM* vm, Value value);

Value vm_stack_pop(VM* vm);