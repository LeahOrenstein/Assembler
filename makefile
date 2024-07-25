CC = gcc
CFLAGS = -ansi -Wall -pedantic
INCLUDES = -I. -Iprocess -Istructures -ItableStructure

# רשימת קבצי המקור
SRCS = Trial.c testing.c utils.c \
       process/preassembler.c process/firstPass.c process/errors.c process/utilsPass.c \
       structures/command.c structures/macro.c structures/memWord.c structures/symbol.c \
       tableStructure/list.c

# יצירת רשימת קבצי האובייקט
OBJS = $(SRCS:.c=.o)

# המטרה הראשית
all: run

# יצירת הקובץ הריצה
run: $(OBJS)
	$(CC) $(CFLAGS) $(INCLUDES) $(OBJS) -o run

# כלל גנרי ליצירת קבצי אובייקט
%.o: %.c
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

# ניקוי
clean:
	del /Q *.o process\*.o structures\*.o tableStructure\*.o run.exe

# תלויות
Trial.o: Trial.c Trial.h process/preassembler.h process/firstPass.h structures/command.h structures/macro.h testing.h
testing.o: testing.c testing.h process/preassembler.h
utils.o: utils.c utils.h
process/preassembler.o: process/preassembler.c process/preassembler.h structures/macro.h structures/command.h tableStructure/list.h
process/firstPass.o: process/firstPass.c process/firstPass.h structures/symbol.h tableStructure/list.h process/errors.h process/utilsPass.h
process/errors.o: process/errors.c process/errors.h
process/utilsPass.o: process/utilsPass.c process/utilsPass.h
structures/command.o: structures/command.c structures/command.h
structures/macro.o: structures/macro.c structures/macro.h tableStructure/list.h structures/command.h
structures/memWord.o: structures/memWord.c structures/memWord.h
structures/symbol.o: structures/symbol.c structures/symbol.h
tableStructure/list.o: tableStructure/list.c tableStructure/list.h