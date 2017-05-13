LDFLAGS = -pthread
CFLAGS = \
	-g -D_GNU_SOURCE \
	-I.

CFLAGS += -Wall
#CFLAGS += -O3

EXAMPLE = \
	example.o temp.o \

PROGRAMS = \
	example \

all: $(PROGRAMS)

example: $(EXAMPLE)
	$(CC) $(CFLAGS) $^ -o $@ $(LDFLAGS)

clean:
	rm -rf $(PROGRAMS) ./*.o ./*.so ./*/*.o ./*/*.so