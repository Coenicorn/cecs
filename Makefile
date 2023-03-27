# makefile template expects filesystem like so:
# 
# parent dir
# 	- src
# 		- main.c
# 	- lib
# 		- libmylibrary.a
# 	- include
# 		- mylibrary.h
# 	- obj
# 	- build


# rudamentary platform detection, default linux
PLATFORM ?= LINUX

ifeq ($(OS),Windows_NT)
	PLATFORM = WINDOWS
else
	PLATFORM = LINUX
endif


# compiler
CC := 

# should point to the executable, too lazy
ifeq ($(PLATFORM),WINDOWS)
	CC = mingw32-make
endif

ifeq ($(PLATFORM),LINUX)
	CC = gcc
endif


# important directories
EXECDIR := ./build
EXEC := 

ifeq ($(PLATFORM),WINDOWS)
	EXEC = $(EXECDIR)/main.exe
else
	EXEC = $(EXECDIR)/main.out
endif

SRCDIR := ./src
OBJDIR := ./obj
INCLUDEDIR := ./include
LIBDIR := ./lib

CFLAGS := -std=c17 -Wall -Wextra -Wpedantic -g -I$(SRCDIR)/ -I$(INCLUDEDIR)/
LFLAGS := -L$(SRCDIR)/ -L$(LIBDIR)/
LDFLAGS := 

# platform specific linker flags
ifeq ($(PLATFORM),WINDOWS)
	LDFLAGS = 
endif

ifeq ($(PLATFORM),LINUX)
	LDFLAGS = 
endif

OBJS := $(wildcard $(SRCDIR)/*.c)
OBJS := $(OBJS:.c=.o)
OBJS := $(subst $(SRCDIR)/,$(OBJDIR)/,$(OBJS))

DEPENDS := $(OBJS:.o=.d)

RM := rmdir

$(EXEC): $(OBJS)
	$(CC) $^ $(LFLAGS) -o $(EXEC) $(LDFLAGS)

-include $(DEPENDS)

$(OBJDIR)/%.o: $(SRCDIR)/%.c
	$(CC) -MD -c $< $(CFLAGS) -o $@

run: $(EXEC)
	@clear
	$(EXEC)

# clean for windows and linux
clean:
ifeq ($(PLATFORM),WINDOWS)
	del *.o *.exe /s
endif

ifeq ($(PLATFORM),LINUX)
	find . -name "*.out" -type f -delete
	find . -name "*.o" -type f -delete
	find . -name "*.d" -type f -delete
endif