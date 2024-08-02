#-*- MakeFile -*-

# Compiler and compiler flags
CXX = g++
CXXFLAGS = -c

# Object files
OBJS = main.o 
TEST_OBJS = unit_test.o tokenizer_test.o parser_test.o
TOKEN_OBJS = token.o tokenizer.o tokentype.o 
PARSER_OBJS = ast.o parser.o ast_base.o

# Directory prefix
SRC = ./src/
TESTS = ./tests/

# Target executable
TARGET = csp 
TEST_TARGET = csp_tests

all: $(TARGET)

test: $(TEST_TARGET)

$(TARGET): $(OBJS) $(TOKEN_OBJS) $(PARSER_OBJS)
	$(CXX) $(OBJS) $(TOKEN_OBJS) $(PARSER_OBJS) -o $(TARGET)

$(TEST_TARGET): $(TEST_OBJS) $(TOKEN_OBJS) $(PARSER_OBJS)
	$(CXX) $(TEST_OBJS) $(TOKEN_OBJS) $(PARSER_OBJS) -o $(TEST_TARGET)


# Module Objects
main.o: $(SRC)tokenizer.h $(SRC)main.cpp
	$(CXX) $(CXXFLAGS) $(SRC)main.cpp


# Token Objects
tokenizer.o: $(SRC)tokenizer.h $(SRC)tokenizer.cpp $(SRC)token.h
	$(CXX) $(CXXFLAGS) $(SRC)tokenizer.cpp

token.o: $(SRC)token.h $(SRC)token.cpp $(SRC)tokentype.h
	$(CXX) $(CXXFLAGS) $(SRC)token.cpp

tokentype.o: $(SRC)tokentype.h $(SRC)tokentype.cpp
	$(CXX) $(CXXFLAGS) $(SRC)tokentype.cpp


# Parser Objects
ast.o: $(SRC)token.h $(SRC)ast_base.h $(SRC)ast.cpp
	$(CXX) $(CXXFLAGS) $(SRC)ast.cpp

ast_base.o: $(SRC)token.h $(SRC)ast_base.h $(SRC)ast_base.cpp
	$(CXX) $(CXXFLAGS) $(SRC)ast_base.cpp

parser.o: $(SRC)parser.h $(SRC)ast.h $(SRC)tokenizer.h $(SRC)token.h $(SRC)parser.cpp
	$(CXX) $(CXXFLAGS) $(SRC)parser.cpp


# Test Objects
unit_test.o: $(TESTS)parser_test.h $(TESTS)tokenizer_test.h $(TESTS)unit_test.cpp
	$(CXX) $(CXXFLAGS) $(TESTS)unit_test.cpp

tokenizer_test.o: $(SRC)tokenizer.h $(TESTS)tokenizer_test.h $(TESTS)tokenizer_test.cpp
	$(CXX) $(CXXFLAGS) $(TESTS)tokenizer_test.cpp

parser_test.o: $(SRC)parser.h $(TESTS)parser_test.h $(TESTS)parser_test.cpp
	$(CXX) $(CXXFLAGS) $(TESTS)parser_test.cpp


.PHONY: clean
clean:
	rm -f *.o
	rm -f $(TARGET) $(TEST_TARGET)

