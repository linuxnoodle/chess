PROJECT:=chess

CC:=g++
LDFLAGS=-O2 -Wall -O2 -std=c++17 -Iinclude -lSDL2 -lSDL2_image
	UNAME:=$(shell uname)

SRCDIR:=src
OBJDIR:=obj

SRC:=$(wildcard $(SRCDIR)/*.cpp)
OBJ:=$(SRC:$(SRCDIR)/%.cpp=$(OBJDIR)/%.o)

$(PROJECT): $(OBJ)
	$(CC) $(OBJ) $(LDFLAGS) -o $@

$(OBJDIR)/%.o: $(SRCDIR)/%.cpp | $(OBJDIR)
	$(CC) $(LDFLAGS) -c $< -o $@

$(OBJDIR):
	mkdir $(OBJDIR)

.PHONY: all
all: clean $(PROJECT)

.PHONY: clean
clean:
	rm -rf $(OBJDIR) $(PROJECT)
