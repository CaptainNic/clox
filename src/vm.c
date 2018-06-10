#include "config.h"
#include "vm.h"

#include <stdio.h>
#include "common.h"
#if DBG_TRACE_EXECUTION
#include "debug.h"
#endif

static void vm_stack_clear(VM* vm) {
    vm->stackTop = vm->stack;
}

void vm_init(VM* vm) {
    vm_stack_clear(vm);
}

void vm_free(VM* vm) {

}

static InterpretResult vm_run(VM* vm) {
    #define READ_BYTE()     (*vm->ip++)
    #define READ_CONST()    (vm->chunk->constants.values[READ_BYTE()])
    
    for (;;) {
#if DBG_TRACE_EXECUTION
        dbg_stack_dump(vm);
        dbg_instr_disassemble(vm->chunk, (unsigned)(vm->ip - vm->chunk->code));
#endif
        uint8_t instr;
        switch (instr = READ_BYTE()) {
            case OP_CONSTANT: {
                Value constant = READ_CONST();
                vm_stack_push(vm, constant);
                break;
            }
            case OP_RETURN: {
                // TODO: temporary code
                printf("%g\n", vm_stack_pop(vm));
                return INTERPRET_OK;
            }
        }
    }

    #undef READ_BYTE
    #undef READ_CONST
}

InterpretResult vm_interpret(VM* vm, Chunk* chunk) {
    vm->chunk = chunk;
    vm->ip = vm->chunk->code;

    return vm_run(vm);
}

void vm_stack_push(VM* vm, Value value) {
    *(vm->stackTop++) = value;
}

Value vm_stack_pop(VM* vm) {
    return *(--vm->stackTop);
}