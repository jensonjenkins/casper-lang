#-*- MakeFile -*-

# Compiler and compiler flags
CXX = g++
CXXFLAGS = -c

# Object files
OBJS = main.o 
TOKEN_OBJS = token.o tokenizer.o tokentype.o

# Directory prefix
PREF = ./src/

# Target executable
TARGET = csp 

all: $(TARGET)

$(TARGET): $(OBJS)$(TOKEN_OBJS)
	$(CXX) $(OBJS)$(TOKEN_OBJS) -o $(TARGET)

main.o: $(PREF)tokenizer.h $(PREF)main.cpp
	$(CXX) $(CXXFLAGS) $(PREF)main.cpp

tokenizer.o: $(PREF)tokenizer.h $(PREF)tokenizer.cpp $(PREF)token.h
	$(CXX) $(CXXFLAGS) $(PREF)tokenizer.cpp

token.o: $(PREF)token.h $(PREF)token.cpp $(PREF)tokentype.h
	$(CXX) $(CXXFLAGS) $(PREF)token.cpp

tokentype.o: $(PREF)tokentype.h $(PREF)tokentype.cpp
	$(CXX) $(CXXFLAGS) $(PREF)tokentype.cpp

.PHONY: clean
clean:
	rm -f $(OBJS) $(TOKEN_OBJS) $(TARGET) 

