#include <stdio.h>
#include "common.h"
#if DBG_TRACE_EXECUTION
#include "debug.h"
#endif
#include "vm.h"

void vm_init(VM* vm) {

}

void vm_free(VM* vm) {

}

static InterpretResult vm_run(VM* vm) {
    #define READ_BYTE()     (*vm->ip++)
    #define READ_CONST()    (vm->chunk->constants.values[READ_BYTE()])
    
    for (;;) {
#if DBG_TRACE_EXECUTION
        dbg_instr_disassemble(vm->chunk, (unsigned)(vm->ip - vm->chunk->code));
#endif
        uint8_t instr;
        switch (instr = READ_BYTE()) {
            case OP_CONSTANT: {
                Value constant = READ_CONST();
                printValue(constant);
                printf("\n");
                break;
            }
            case OP_RETURN: {
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
