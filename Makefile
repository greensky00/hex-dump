LDFLAGS = -pthread
CXXFLAGS = \
	-g -D_GNU_SOURCE \
	-I.

CXXFLAGS += -Wall
#CXXFLAGS += -O3

EXAMPLE = \
	example.o \

PROGRAMS = \
	example \

all: $(PROGRAMS)

tests/latency_test: $(EXAMPLE)
	$(CXX) $(CXXFLAGS) $^ -o $@ $(LDFLAGS)

clean:
	rm -rf $(PROGRAMS) ./*.o ./*.so ./*/*.o ./*/*.so