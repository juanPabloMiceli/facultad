.POSIX:
.SUFFIXES: .cpp

CXX = g++
CXXFLAGS = -std=c++11 -Wall -g
LDFLAGS = -pthread

.cpp:
	$(CXX) $(CXXFLAGS) $(LDFLAGS) -o $@ $< $(LDLIBS)

BIN = ej1 \
	  ej1_race_cond \
	  ej2 \
	  ej3 \
	  ej9_p4

SRC = $(BIN:=.cpp)



all: $(BIN) ls_copy

# all: clean ls_copy

ls_copy:
	gcc ls_copy.c -o ls_copy

clean:
	rm ls_copy
	rm $(BIN)
