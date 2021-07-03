OBJS = \
 main.o \
 utils.o \
 opcodes.o \
 cpu.o \
 display.o \

LINK_TARGET = chip8.o

REBUILDABLES = $(OBJS) $(LINK_TARGET)

clean:
	rm $(REBUILDABLES)
	echo "cleaned!"

all: $(LINK_TARGET)
	echo "all built!"

$(LINK_TARGET): $(OBJS)
	gcc -Wall -I /usr/local/include/SDL2 -g -o $@ $^ -lSDL2

%.o: %.c
	gcc -Wall -g -o $@ -c $<

main.o: opcodes.h utils.h display.h
utils.o: utils.h
opcodes.o: opcodes.h utils.h
cpu.o: memory.h register.h input.h timer.h opcodes.h
