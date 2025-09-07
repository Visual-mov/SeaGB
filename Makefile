CC = gcc
CCFLAGS = -pedantic -Wall -Wextra
LFLAGS = -lSDL2

SRCDIR = ./src
INCDIR = ./include
OBJDIR = ./obj
BINDIR = ./

EXEC = ./seagb

SOURCES = $(wildcard $(SRCDIR)/*.c)
OBJECTS = $(patsubst $(SRCDIR)/%.c,$(OBJDIR)/%.o,$(SOURCES))

INCLUDE_FLAGS = -I$(INCDIR)

.PHONY: all clean mkdir_obj

all: mkdir_obj $(BINDIR)/$(EXEC)

$(BINDIR)/$(EXEC): $(OBJECTS)
	$(CC) $(OBJECTS) -o $@ $(LFLAGS)

$(OBJDIR)/%.o: $(SRCDIR)/%.c
	mkdir -p $(OBJDIR)
	$(CC) $(CFLAGS) $(INCLUDE_FLAGS) -c $< -o $@

mkdir_obj:
	mkdir -p $(OBJDIR)

clean:
	rm -rf $(OBJDIR) $(EXEC)