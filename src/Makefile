##
# Makefile
# @author Rafael
##

# Compiler Options
CC = g++
CC_FLAGS = -Wall -std=c++11

MAIN = main
SOURCES = $(MAIN).cpp preprocessador.cpp montador.cpp
HEADERS = mensagens.h preprocessador.h montador.h

EXECUTABLE = myprogram

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
OBJECTS = $(MAIN).o montador.o preprocessador.o # lexer.o parser.o

##
# Modules:
##
preprocessador.o: preprocessador.cpp preprocessador.h
	$(CC) $(CCFLAGS) -c preprocessador.cpp

#lexer.o: lexer.cpp variaveis.h
#	$(CC) $(CCFLAGS) -c lexer.cpp

#parser.o: parser.cpp parser.h
#	$(CC) $(CCFLAGS) -c parser.cpp

montador.o: montador.h montador.cpp preprocessador.o #lexer.o parser.o
	$(CC) $(CCFLAGS) -c montador.cpp

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
.PHONY = docs
docs: $(EXECUTABLE)
	# Generate only for Funcional Version
	doxygen Doxyfile
