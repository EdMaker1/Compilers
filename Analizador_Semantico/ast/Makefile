CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra

SOURCES = traductor.cpp lexer.cpp parser.cpp ast.cpp symtable.cpp error.cpp checker.cpp
OBJECTS = $(SOURCES:.cpp=.o)
TARGET = traductor

all: $(TARGET)

$(TARGET): $(OBJECTS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJECTS)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f $(OBJECTS) $(TARGET)

.PHONY: all clean
