CC = g++
CFLAGS = --std=c++17 -Wall -Werror -pedantic -g
LIB = -lsfml-graphics -lsfml-audio -lsfml-window -lsfml-system -lboost_unit_test_framework

# Your .hpp files
DEPS = Sokoban.hpp

# Your compiled .o files
OBJECTS = main.o Sokoban.o

# The name of your program
PROGRAM = Sokoban

LIBRARY = Sokoban.a

# Default target
all: $(PROGRAM) $(LIBRARY) test

# Rule to make Sokoban executable
$(PROGRAM): $(OBJECTS)
	$(CC) $(CFLAGS) -o $@ $^ $(LIB)

# Rule to make Sokoban library
$(LIBRARY): Sokoban.o
	ar rcs $@ $^

# Rule to make test executable
test: test.o Sokoban.o
	$(CC) $(CFLAGS) -o $@ $^ $(LIB)

# Generic rule to make .o files from corresponding .cpp file
%.o: %.cpp $(DEPS)
	$(CC) $(CFLAGS) -c $<

# Clean rule
clean:
	rm -f *.o $(PROGRAM) $(LIBRARY) test

# Lint rule
lint:
	cpplint *.cpp *.hpp
