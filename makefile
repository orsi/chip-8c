FILES = main.c chip8.c opcodes.c ui.c
FLAGS = -o ./build/chip8c
LDFLAGS = -framework SDL2 -F /Library/Frameworks/ -I /Library/Frameworks/SDL2.framework/Headers

chip8c:
	clang $(FILES) $(FLAGS) $(LDFLAGS)