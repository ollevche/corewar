
all: vm asm

vm:
	make -C ../virtual_machine
	cp ../virtual_machine/corewar ./

vmre:
	make re -C ../virtual_machine
	cp ../virtual_machine/corewar ./

asm:
	make -C ../compiler
	cp ../compiler/asm ./

asmre:
	make re -C ../compiler
	cp ../compiler/asm ./