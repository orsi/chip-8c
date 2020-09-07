# Chip-8C
Chip-8C is a [Chip-8](https://en.wikipedia.org/wiki/CHIP-8) emulator written in C by Jonathon Orsi.

![Space Invaders](https://raw.githubusercontent.com/orsi/chip8c/master/chip8c-cover.png)

# Installing
```
$ git clone https://github.com/orsi/chip8c
$ cd chipc
$ make
```

`make` will compile to ./build/chip8c

# Run
```
$ ./build/chip8c path/to/chip8roms/file.name
```

# Dependencies
Chip8C uses the SDL2 library for both graphics and audio output. You can download the library [here](https://www.libsdl.org/download-2.0.php). You will most likely have to edit the `makefile` and change the `LDFLAGS` path to where your version of SDL2 is installed. You may also have to change `-framework SDL2 -F /Library/Frameworks/` to `-l SDL2 -L /Library/Frameworks/`, i.e. changing the compiler flags to recognize SDL2 as a library rather than framework, depending on your installation.
```
FILES = ./src/*.c
FLAGS = -o ./build/chip8c
LDFLAGS = -framework SDL2 -F /Library/Frameworks/ -I /Library/Frameworks/SDL2.framework/Headers

chip8c:
	clang $(FILES) $(FLAGS) $(LDFLAGS)
```

# Resources and Credit
[Chip-8 Wikepedia](https://en.wikipedia.org/wiki/CHIP-8)
[cookerlyk/Chip8](https://github.com/cookerlyk/Chip8) - C code reference
[How to write an emulator (CHIP-8 interpreter) - Lawrence Muller](http://www.multigesture.net/articles/how-to-write-an-emulator-chip-8-interpreter/) - More in-depth details on opcode functionality
[BC_test.ch8](https://slack-files.com/T3CH37TNX-F3RF5KT43-0fb93dbd1f) and [BC_test.txt](https://slack-files.com/T3CH37TNX-F3RKEUKL4-b05ab4930d) for validating each opcode