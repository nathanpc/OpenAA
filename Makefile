PROJECT = openaa

CC = g++
RM = rm -f
GDB = gdb
MKDIR = mkdir -p

SRCDIR = src
INCDIR = include
BUILDDIR := build
TARGET = $(PROJECT)

SRCEXT := cpp
SOURCES := $(shell find $(SRCDIR) -type f -name *.$(SRCEXT))
OBJECTS := $(patsubst $(SRCDIR)/%,$(BUILDDIR)/%,$(SOURCES:.$(SRCEXT)=.o))

CFLAGS = -Wall -I $(INCDIR)
LDFLAGS = -lportaudio

all: $(TARGET)

$(TARGET): $(OBJECTS)
	$(CC) $(CFLAGS) $(OBJECTS) -o $@ $(LDFLAGS)

$(BUILDDIR)/%.o: $(SRCDIR)/%.$(SRCEXT)
	@$(MKDIR) $(BUILDDIR)
	$(CC) $(CFLAGS) -c $< -o $@

debug: CFLAGS += -g3 -DDEBUG
debug: $(TARGET)
	$(GDB) $(TARGET)

clean:
	$(RM) -r $(BUILDDIR)
	$(RM) $(TARGET)
	$(RM) valgrind.log

