# Makefile for OOP-Game project

# 1. Compiler and flags
CXX := g++
CXXFLAGS := -std=c++17 -Wall -Wextra -O2 -Iinclude

# 2. Source and object files (exclude skip1.cpp and skip2.cpp)
SRCS := $(filter-out FarmMain.cpp testBankAccount.cpp text.cpp timerTest.cpp,$(wildcard *.cpp))
OBJS := $(SRCS:.cpp=.o)

# 3. Name of the final executable
TARGET := farmGame

# 4. Default target: build the executable
# Default target: builds the main executable
all: $(TARGET)

# 5. Link object files into the executable
$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $^

# 6. Compile .cpp files to .o
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# 7. Clean up build artifacts
clean:
	$(RM) $(OBJS) $(TARGET)
