PROJECT = openaa

CC = g++
RM = rm -f
GDB = gdb
MKDIR = mkdir -p

SRCDIR = src
INCDIR = include
BUILDDIR := build
TARGET = $(BUILDDIR)/bin/$(PROJECT)

SRCEXT := cpp
SOURCES := $(shell find $(SRCDIR) -type f -name *.$(SRCEXT))
OBJECTS := $(patsubst $(SRCDIR)/%,$(BUILDDIR)/obj/%,$(SOURCES:.$(SRCEXT)=.o))

CFLAGS = -Wall -I $(INCDIR)
LDFLAGS = -lportaudio -lm -lfftw3

all: $(TARGET)

$(TARGET): $(OBJECTS)
	$(CC) $(CFLAGS) $(OBJECTS) -o $@ $(LDFLAGS)

$(BUILDDIR)/obj/%.o: $(SRCDIR)/%.$(SRCEXT)
	@$(MKDIR) $(BUILDDIR)/bin
	@$(MKDIR) $(BUILDDIR)/obj
	@$(MKDIR) $(BUILDDIR)/obj/Device
	$(CC) $(CFLAGS) -c $< -o $@

run: $(TARGET)
	./$(TARGET)

debug: CFLAGS += -g3 -DDEBUG
debug: $(TARGET)
	$(GDB) $(TARGET)

clean:
	$(RM) -r $(BUILDDIR)
	$(RM) valgrind.log

