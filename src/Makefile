##
# Makefile
# @author Rafael
##

# Compiler Options
CC = g++
CC_FLAGS = -Wall -std=c++11

MAIN = main
SOURCES = $(MAIN).cpp preprocessor.cpp assembler.cpp lexer.cpp
HEADERS = msgs_pt.h preprocessor.h assembler.h lexer.h

EXECUTABLE = yla

# Test Options
TEST_FILES_DIR = ./test_files


##
# Recipes:
##
.PHONY = ALL
ALL: $(SOURCES) $(HEADERS) $(EXECUTABLE)

# Compile
$(MAIN): $(MAIN).cpp
	$(CC) $(CC_FLAGS) $(NAME).cpp -o $(NAME).run

@echo Objects:$(OBJECTS)
OBJECTS = $(MAIN).o assembler.o preprocessor.o lexer.o # parser.o

##
# Modules:
##
preprocessor.o: preprocessor.cpp preprocessor.h
	$(CC) $(CCFLAGS) -c preprocessor.cpp

#lexer.o: lexer.cpp variaveis.h
#	$(CC) $(CCFLAGS) -c lexer.cpp

parser.o: parser.cpp parser.h
	$(CC) $(CCFLAGS) -c parser.cpp

assembler.o: assembler.h assembler.cpp preprocessor.o lexer.o # parser.o
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

clear-all: clean-objects
	rm -vf $(EXECUTABLE)

##
# Tests
##
.PHONY = test
test:
	@echo "TESTES Concluídos!"

##
# Documentation
##
.PHONY = doc
docs: $(EXECUTABLE)
	# Generate only for Funcional Version
	doxygen Doxyfile
