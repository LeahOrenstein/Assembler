# Compiler
CC = gcc

# Compiler flags
CFLAGS = -ansi -pedantic -Wall

# Include directories
INCLUDES = -I. -Iprocess -Iprocess/validationFunctions -Istructures -ItableStructure -Idefinitions

# Source files
SRCS = Trial.c testing.c utils.c \
       process/preassembler.c process/firstPass.c process/utilsPass.c \
       process/validationFunctions/errors.c process/validationFunctions/utilsError.c \
       process/processingFunctions/processingLineFunct.c \
       structures/command.c structures/macro.c structures/memWord.c structures/symbol.c \
       structures/symbolAppearance.c \
       tableStructure/list.c \
       definitions/definitions.c

# Object files
OBJS = $(SRCS:.c=.o)

# Default target
all: run

# Linking the final executable
run: $(OBJS)
	$(CC) $(CFLAGS) $(INCLUDES) $(OBJS) -o $@

# Generic rule for creating object files
%.o: %.c
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

# Clean target
clean:
	del /Q *.o process\*.o process\validationFunctions\*.o process\processingFunctions\*.o structures\*.o tableStructure\*.o definitions\*.o run.exe

# Dependencies
Trial.o: Trial.c Trial.h process/preassembler.h process/firstPass.h structures/command.h structures/macro.h testing.h
testing.o: testing.c testing.h process/preassembler.h
utils.o: utils.c utils.h
process/preassembler.o: process/preassembler.c process/preassembler.h structures/macro.h structures/command.h tableStructure/list.h utils.h
process/firstPass.o: process/firstPass.c process/firstPass.h structures/symbol.h tableStructure/list.h process/validationFunctions/errors.h process/utilsPass.h utils.h
process/utilsPass.o: process/utilsPass.c process/utilsPass.h utils.h tableStructure/list.h
process/validationFunctions/errors.o: process/validationFunctions/errors.c process/validationFunctions/errors.h process/utilsPass.h tableStructure/list.h
process/validationFunctions/utilsError.o: process/validationFunctions/utilsError.c process/validationFunctions/utilsError.h
process/processingFunctions/processingLineFunct.o: process/processingFunctions/processingLineFunct.c process/processingFunctions/processingLineFunct.h
structures/command.o: structures/command.c structures/command.h
structures/macro.o: structures/macro.c structures/macro.h tableStructure/list.h structures/command.h
structures/memWord.o: structures/memWord.c structures/memWord.h
structures/symbol.o: structures/symbol.c structures/symbol.h process/preassembler.h
structures/symbolAppearance.o: structures/symbolAppearance.c structures/symbolAppearance.h
tableStructure/list.o: tableStructure/list.c tableStructure/list.h
definitions/definitions.o: definitions/definitions.c definitions/definitions.h