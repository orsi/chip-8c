FLAGS = -Wall -pedantic -o ./build/chip8c
LINKER_FLAGS = -lSDL2 
LIB_SDL_MAIN = -L /Library/Frameworks/SDL2/Headers/
FILES = main.c

chip8c:
	clang $(FILES) $(INCLUDE) $(LIB) $(LIB_SDL_MAIN) $(FLAGS) $(LINKER_FLAGS)