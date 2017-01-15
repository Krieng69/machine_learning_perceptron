# the compiler to use
CC = clang

# compiler flags:
#  -g    adds debugging information to the executable file
#  -Wall turns on most, but not all, compiler warnings
CFLAGS  = -Wall -Werror
  
# files to link:
LFLAGS =
  
# the source files to compile (and link):
SOURCES = perceptron.c parser.c

# name for the resulting executable
TARGET = perceptron
  
all: $(TARGET)
  
$(TARGET): $(SOURCES)
	$(CC) $(CFLAGS) -o $(TARGET) $(SOURCES) $(LFLAGS)
