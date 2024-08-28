# Compiler
CC = gcc

# Source files
SRCS = hcompress.c linkedList.c

# Object files
OBJS = $(SRCS:.c=.o)

# Executable name
TARGET = hcompress

# Compilation flags
CFLAGS = -Wall -g

# Build the target executable
$(TARGET): $(OBJS)
	$(CC) $(OBJS) -o $(TARGET)

# Rule to build each .o file from .c files
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# Clean up the build
clean:
	rm -f $(OBJS) $(TARGET)
