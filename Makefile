#-*- MakeFile -*-

# Compiler and compiler flags
CXX = g++-14
CXXFLAGS = -c

# Object files
OBJS = main.o

# Target executable
TARGET = csp 

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) $(OBJS) -o $(TARGET)

main.o: ./src/main.cpp
	$(CXX) $(CXXFLAGS) ./src/main.cpp

.PHONY: clean
clean:
	rm -f $(OBJS) $(TARGET)


