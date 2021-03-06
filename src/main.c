#include "config.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "common.h"
#include "vm.h"

static void repl(VM* vm) {
	char line[1024];

	for (;;) {
		printf("> ");
		if (!fgets(line, sizeof(line), stdin)) {
			printf("\n");
			break;
		}

		vm_interpret(vm, line);
	}
}

static char* read_file(const char* path) {
	FILE* file = fopen(path, "rb");
	if (file == NULL) {
		fprintf(stderr, "Could not open file '%s'.\n", path);
		exit(74);
	}

	fseek(file, 0L, SEEK_END);
	size_t size = ftell(file);
	rewind(file);

	char* buffer = (char*)malloc(size + 1);
	if (buffer == NULL) {
		fprintf(stderr, "Not enough memory to read '%s'.\n", path);
		exit(74);
	}

	size_t bytes_read = fread(buffer, sizeof(char), size, file);
	if (bytes_read < size) {
		fprintf(stderr, "Failed to read file '%s'.\n", path);
		exit(74);
	}
	buffer[bytes_read] = '\0';

	fclose(file);
	return buffer;
}

static void run_file(VM* vm, const char* path) {
	char* source = read_file(path);
	InterpretResult result = vm_interpret(vm, source);
	free(source);

	switch (result) {
		case INTERPRET_COMPILE_ERROR: exit(65);
		case INTERPRET_RUNTIME_ERROR: exit(70);
	}
}

int main(int argc, const char* argv[]) {
	VM vm;

	vm_init(&vm);

	if (argc == 1) {
		repl(&vm);
	} else if (argc == 2) {
		run_file(&vm, argv[1]);
	} else {
		fprintf(stderr, "Usage: %s [path]\n", argv[0]);
		exit(64);
	}

	vm_free(&vm);

	return 0;
}