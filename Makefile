OBJS = \
 main.o \
 utils.o \
 opcodes.o \

LINK_TARGET = chip8.o

REBUILDABLES = $(OBJS) $(LINK_TARGET)

clean:
	rm $(REBUILDABLES)
	echo "cleaned!"

all: $(LINK_TARGET)
	echo "all built!"

$(LINK_TARGET): $(OBJS)
	gcc -Wall -g -o $@ $^

%.o: %.c
	gcc -Wall -g -o $@ -c $<

main.o: opcodes.h utils.h
utils.o: utils.h
opcodes.o: opcodes.h utils.h
