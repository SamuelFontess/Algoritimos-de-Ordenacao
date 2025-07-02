
CXX = g++
CXXFLAGS = -std=c++17 -Wall -O2

SRCDIR = .
BUILDDIR = ../build

# Source files
SRCS = \
	$(SRCDIR)/main.cpp \
	$(SRCDIR)/utils/ArrayGenerator.cpp \
	$(SRCDIR)/bubble_sort/BubbleSort.cpp \
	$(SRCDIR)/insertion_sort/InsertionSort.cpp \
	$(SRCDIR)/selection_sort/SelectionSort.cpp \
	$(SRCDIR)/merge_sort/MergeSort.cpp \
	$(SRCDIR)/quick_sort/QuickSort.cpp

# Object files
OBJS = $(patsubst $(SRCDIR)/%.cpp, $(BUILDDIR)/%.o, $(SRCS))

TARGET = $(BUILDDIR)/sorting_analysis

all: $(TARGET)

$(TARGET): $(OBJS)
	mkdir -p $(@D)
	$(CXX) $(CXXFLAGS) $(OBJS) -o $@

$(BUILDDIR)/%.o: $(SRCDIR)/%.cpp
	mkdir -p $(@D)
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -rf $(BUILDDIR)

.PHONY: all clean

