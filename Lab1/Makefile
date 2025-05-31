CXX = g++
CXXFLAGS = -Werror -Wpedantic -Wall -std=c++20

BUILDDIR = build
BINDIR = bin

TARGET = $(BINDIR)/read_BMP
ALLNEWBMP = BMP_clockwise.bmp BMP_clockwise_filter.bmp BMP_contra_clockwise.bmp BMP_contra_clockwise_filter.bmp 

SRCS = $(wildcard *.cpp)
OBJS = $(patsubst %.cpp,$(BUILDDIR)/%.o,$(SRCS))

all: $(BUILDDIR) $(BINDIR) $(TARGET)

$(BUILDDIR):
	@mkdir -p $(BUILDDIR)

$(BINDIR):
	@mkdir -p $(BINDIR)

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $^

$(BUILDDIR)/%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

run: $(TARGET)
	./$(TARGET) example.bmp

test: $(TARGET)
	valgrind --leak-check=full ./$(TARGET) example.bmp
	
clean:
	rm -rf $(BUILDDIR) $(BINDIR) $(ALLNEWBMP)

.PHONY: all clean run run-test
