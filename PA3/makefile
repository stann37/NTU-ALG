# Compiler
CC = g++

# Compiler flags
CFLAGS = -Wall -std=c++11 -O3  # Use -O3 optimization level

# Directories
SRCDIR = src
BINDIR = bin

# Source files
SOURCES = $(SRCDIR)/main.cpp $(SRCDIR)/CycleBreaking.cpp
HEADERS = $(SRCDIR)/CycleBreaking.h

# Target executable
TARGET = $(BINDIR)/cb

all: $(TARGET)

$(TARGET): $(SOURCES) $(HEADERS)
	$(CC) $(CFLAGS) -o $(TARGET) $(SOURCES)

clean:
	rm -f $(TARGET)
