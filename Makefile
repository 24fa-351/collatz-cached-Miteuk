# Compiler to use
CC = gcc

# Compiler flags
CFLAGS = -Wall

# Executable name
TARGET = collatz

# Source files
SRCS = main.c collatz.c

# Rule to create the executable
$(TARGET): $(SRCS)
	$(CC) $(CFLAGS) -o $(TARGET) $(SRCS)

# Clean command to remove the executable
clean:
	rm -f $(TARGET)