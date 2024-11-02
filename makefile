# Makefile

# Compiler
CXX = g++
CXXFLAGS = -Wall -std=c++11

# Source files
SOURCES = main.cpp console_menu.cpp file_manager.cpp utils.cpp bookseller.cpp textbook.cpp

# Output executable
OUTPUT = course_project

# Rule to build the program
all: $(SOURCES)
	$(CXX) $(CXXFLAGS) -o $(OUTPUT) $(SOURCES)

# Clean rule to remove the compiled files
clean:
	rm -f $(OUTPUT)
