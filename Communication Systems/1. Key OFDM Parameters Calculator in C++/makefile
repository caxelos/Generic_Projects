# Copyright (c) 2025 Christos Axelos.  
# Provided solely for recruitment evaluation.  
# See LICENSE.txt for full terms.


# Makefile

# Compiler
CXX = g++

# Compiler flags
CXXFLAGS = -Wall -Wextra -Wpedantic -Iinc

# Target executable
TARGET = main

# Source and include directories
SRC_DIR = src
INC_DIR = inc
BUILD_DIR = build
OBJ_DIR = $(BUILD_DIR)/obj

# Source and header files
SRCS := $(wildcard $(SRC_DIR)/*.cpp)
HEADERS := $(wildcard $(INC_DIR)/*.hpp)
OBJS := $(patsubst $(SRC_DIR)/%.cpp,$(OBJ_DIR)/%.o,$(SRCS))

# Default rule
all: $(BUILD_DIR)/$(TARGET)

# Link object files into the target
$(BUILD_DIR)/$(TARGET): $(OBJS) | $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) $(OBJS) -o $@

# Compile .cpp into .o, each depending on headers
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp $(HEADERS) | $(OBJ_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Ensure build directories exist
$(BUILD_DIR) $(OBJ_DIR):
	mkdir -p $@

# Clean up generated files
clean:
	rm -rf $(BUILD_DIR)