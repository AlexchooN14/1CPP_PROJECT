# Compiler
CXX = g++

# Compiler flags
CXXFLAGS = -Wall -Wextra -std=c++11

# Source files
SRC = main.cpp console_menu.cpp textbook.cpp bookseller.cpp utilities.cpp data_management.cpp

# Executable name
EXEC = MyBooksellerApp

# Default target to build the executable
$(EXEC): $(SRC)
	$(CXX) $(CXXFLAGS) -o $@ $^

# Clean target to remove the executable
clean:
	rm -f $(EXEC)

# Phony targets
.PHONY: clean
