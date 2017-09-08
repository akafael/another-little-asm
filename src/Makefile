##
# Makefile
# @authors Rafael e Joao Pedro
##

# Compiler Options
CC = g++
CC_FLAGS = -Wall -std=c++11 -ggdb

MAIN = main
SOURCES = $(MAIN).cpp preprocessor.cpp assembler.cpp lexer.cpp macroeval.cpp \
	parser.cpp
HEADERS = msgs_pt.h preprocessor.h assembler.h lexer.h macroeval.h parser.h

EXECUTABLE = yla

# Test Options
TEST_FILES_DIR = ../test_files

# input test files
TEST_FILES_ASM = $(wildcard $(TEST_FILES_DIR)/*.asm)
TEST_FILES_PRE = $(addsuffix .pre, $(basename $(TEST_FILES_ASM)))
TEST_FILES_MCR = $(addsuffix .mcr, $(basename $(TEST_FILES_ASM)))
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
OBJECTS = $(MAIN).o assembler.o preprocessor.o lexer.o macroeval.o parser.o

##
# Modules:
##
preprocessor.o: preprocessor.cpp preprocessor.h
	$(CC) $(CCFLAGS) -c preprocessor.cpp

macroeval.o: macroeval.cpp macroeval.h
	$(CC) $(CCFLAGS) -c macroeval.cpp

lexer.o: lexer.cpp lexer.h
	$(CC) $(CCFLAGS) -c lexer.cpp

parser.o: parser.cpp parser.h
	$(CC) $(CCFLAGS) -c parser.cpp

assembler.o: assembler.cpp assembler.h msgs_pt.h preprocessor.o lexer.o macroeval.o parser.o
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
	rm -vf $(OBJECTS);

clear-test:
	rm -vf $(TEST_FILES_PRE) $(TEST_FILES_MCR) $(TEST_FILES_OBJ);

clear-docs:
	rm -vrf ../docs/*;

clear-all: clear-objects clear-test
	rm -vf $(EXECUTABLE);

##
# Automatic Tests
##
.PHONY = test
test: $(EXECUTABLE) test-precompiler test-macroeval test-assembler
	@echo "\033[92mTESTES Concluídos!\033[0m"

test-precompiler: $(TEST_FILES_ASM)
	@echo "\033[33mTESTES precompiler concluídos!\n \033[0m"

test-macroeval: $(TEST_FILES_PRE)
	@echo "\033[33mTESTES macroeval concluídos!\n \033[0m"

test-assembler: $(TEST_FILES_MCR)
	@echo "\033[33mTESTES assembler concluídos!\n \033[0m"

# Run precompiler for all .asm files
$(TEST_FILES_ASM): $(EXECUTABLE)
	./$< -p $@ $(addsuffix .pre, $(basename $@))

# Evalute Macros for all .pre files
$(TEST_FILES_PRE): $(EXECUTABLE) test-precompiler
	./$< -m $@ $(addsuffix .mcr, $(basename $@))

# Run assembler for all .mcr files
$(TEST_FILES_MCR): $(EXECUTABLE) test-macroeval
	./$< -o $@ $(addsuffix .obj, $(basename $@))

##
# Documentation
##
.PHONY = doc
docs: $(EXECUTABLE)
	# Generate only for Funcional Version
	doxygen Doxyfile
