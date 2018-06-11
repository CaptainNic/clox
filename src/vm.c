#include "config.h"
#include "vm.h"

#include <stdio.h>
#include "common.h"
#include "compiler.h"
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
    #define BINARY_OP(op)               \
        do {                            \
            double a = vm_stack_pop(vm);\
            double b = vm_stack_pop(vm);\
            vm_stack_push(vm, a op b);  \
        } while (false)

    for (;;) {
#if DBG_TRACE_EXECUTION
        dbg_instr_disassemble(vm->chunk, (unsigned)(vm->ip - vm->chunk->code));
#endif
        uint8_t instr;
        switch (instr = READ_BYTE()) {
            case OP_CONSTANT: {
                Value constant = READ_CONST();
                vm_stack_push(vm, constant);
                break;
            }
            case OP_ADD:        BINARY_OP(+); break;
            case OP_SUBTRACT:   BINARY_OP(-); break;
            case OP_MULTIPLY:   BINARY_OP(*); break;
            case OP_DIVIDE:     BINARY_OP(/); break;
            case OP_NEGATE: {
                vm_stack_push(vm, -vm_stack_pop(vm));
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
    #undef BINARY_OP
}

InterpretResult vm_interpret(VM* vm, const char* source) {
    compile(source);
    return INTERPRET_OK;
}

//TODO: error handling
void vm_stack_push(VM* vm, Value value) {
    *(vm->stackTop++) = value;
#if DBG_TRACE_EXECUTION
    printf("%g -> ", value);
    dbg_stack_dump(vm);
#endif
}

//TODO: error handling
Value vm_stack_pop(VM* vm) {
    Value value = *(--vm->stackTop);
#if DBG_TRACE_EXECUTION
    printf("%g <- ", value);
    dbg_stack_dump(vm);
#endif
    return value;
}