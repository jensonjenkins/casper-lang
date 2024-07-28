#-*- MakeFile -*-

# Compiler and compiler flags
CXX = g++
CXXFLAGS = -c

# Object files
OBJS = main.o 
TEST_OBJS = tests.o 
TOKEN_OBJS = token.o tokenizer.o tokentype.o 

# Directory prefix
PREF = ./src/
TEST_PREF = ./tests/

# Target executable
TARGET = csp 
TEST_TARGET = csp_tests

all: $(TARGET)

test: $(TEST_TARGET)

$(TARGET): $(OBJS)$(TOKEN_OBJS)
	$(CXX) $(OBJS)$(TOKEN_OBJS) -o $(TARGET)

$(TEST_TARGET): $(TEST_OBJS) $(TOKEN_OBJS)
	$(CXX) $(TEST_OBJS)$(TOKEN_OBJS) -o $(TEST_TARGET)

main.o: $(PREF)tokenizer.h $(PREF)main.cpp
	$(CXX) $(CXXFLAGS) $(PREF)main.cpp

tests.o: $(PREF)tokenizer.h $(TEST_PREF)tests.cpp
	$(CXX) $(CXXFLAGS) $(TEST_PREF)tests.cpp

tokenizer.o: $(PREF)tokenizer.h $(PREF)tokenizer.cpp $(PREF)token.h
	$(CXX) $(CXXFLAGS) $(PREF)tokenizer.cpp

token.o: $(PREF)token.h $(PREF)token.cpp $(PREF)tokentype.h
	$(CXX) $(CXXFLAGS) $(PREF)token.cpp

tokentype.o: $(PREF)tokentype.h $(PREF)tokentype.cpp
	$(CXX) $(CXXFLAGS) $(PREF)tokentype.cpp


.PHONY: clean
clean:
	rm -f $(TEST_OBJS) $(OBJS) $(TOKEN_OBJS) $(TEST_TARGET) $(TARGET)

