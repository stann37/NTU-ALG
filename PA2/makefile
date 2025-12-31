# Compiler
CC = g++

# Compiler flags
CFLAGS = -Wall -std=c++11 -O2  # Use -O2 optimization level

# Directories
SRCDIR = src
BINDIR = bin

# Source files
SOURCES = $(SRCDIR)/main.cpp $(SRCDIR)/maxPlanerSubset.cpp
HEADERS = $(SRCDIR)/maxPlanerSubset.h

# Target executable
TARGET = $(BINDIR)/mps

all: $(TARGET)

$(TARGET): $(SOURCES) $(HEADERS)
	$(CC) $(CFLAGS) -o $(TARGET) $(SOURCES)

clean:
	rm -f $(TARGET)
