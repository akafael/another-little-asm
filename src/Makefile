##
# Makefile
# @authors Rafael e Joao Pedro
##

# Compiler Options
CC = g++
CC_FLAGS = -Wall -std=c++11 -ggdb

MAIN = main
SOURCES = $(MAIN).cpp preprocessor.cpp assembler.cpp lexer.cpp
HEADERS = msgs_pt.h preprocessor.h assembler.h lexer.h

EXECUTABLE = yla

# Test Options
TEST_FILES_DIR = ../test_files

# input test files
TEST_FILES_ASM = $(wildcard $(TEST_FILES_DIR)/*.asm)
TEST_FILES_PRE = $(addsuffix .pre, $(basename $(TEST_FILES_ASM)))
TEST_FILES_OBJ = $(addsuffix .obj, $(basename $(TEST_FILES_ASM)))

##
# Recipes:
##
.PHONY = ALL
ALL: $(SOURCES) $(HEADERS) $(EXECUTABLE)

# Compile
$(MAIN): $(MAIN).cpp
	$(CC) $(CC_FLAGS) $(NAME).cpp

@echo Objects:$(OBJECTS)
OBJECTS = $(MAIN).o assembler.o preprocessor.o lexer.o # parser.o

##
# Modules:
##
preprocessor.o: preprocessor.cpp preprocessor.h
	$(CC) $(CCFLAGS) -c preprocessor.cpp

lexer.o: lexer.cpp lexer.h
	$(CC) $(CCFLAGS) -c lexer.cpp

parser.o: parser.cpp parser.h
	$(CC) $(CCFLAGS) -c parser.cpp

assembler.o: assembler.cpp assembler.h  msgs_pt.h preprocessor.o lexer.o # parser.o
	$(CC) $(CCFLAGS) -c assembler.cpp

##
# Main files:
##
$(MAIN).o: $(MAIN).cpp $(HEADERS)
	$(CC) $(CCFLAGS) -c $(MAIN).cpp

$(EXECUTABLE): $(OBJECTS)
	$(CC) $(CCFLAGS) $(OBJECTS) -o $@

##
# Remove generated files
##
.PHONY = clear
clear-objects:
	rm -vf $(OBJECTS)

clear-docs:
	rm -vrf ../docs/*

clear-all: clear-objects
	rm -vf $(EXECUTABLE)

##
# Automatic Tests
##
.PHONY = test
test: $(EXECUTABLE) test-precompiler test-assembler
	@echo "TESTES Concluídos!"

test-precompiler: $(TEST_FILES_ASM)
	@echo "TESTES precompiler concluídos!"

test-assembler: $(TEST_FILES_PRE)
	@echo "TESTES assembler concluídos!"

# Run precompiler for all .asm files
$(TEST_FILES_ASM): $(EXECUTABLE)
		./$< -p $@ $@.pre

# Run assembler for all .pre files
$(TEST_FILES_PRE): $(EXECUTABLE) test-precompiler
	./$< -o $@ $@.obj

##
# Documentation
##
.PHONY = doc
docs: $(EXECUTABLE)
	# Generate only for Funcional Version
	doxygen Doxyfile
