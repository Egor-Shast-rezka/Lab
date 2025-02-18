CXX = g++
CXXFLAGS = -Werror -Wpedantic -Wall -std=c++17 -Iinclude

SRCDIR = src
INCDIR = include
OBJDIR = obj
BINDIR = bin
TESTDIR = tests
DOCDIR = doc

TARGET = $(BINDIR)/Poker

SRCS = $(wildcard $(SRCDIR)/*.cpp)
OBJS = $(patsubst $(SRCDIR)/%.cpp, $(OBJDIR)/%.o, $(SRCS))

TEST_SRCS = $(wildcard $(TESTDIR)/*.cpp)
TEST_OBJS = $(patsubst $(TESTDIR)/%.cpp, $(OBJDIR)/%.o, $(TEST_SRCS))

all: $(TARGET)

$(TARGET): $(OBJS)
	@mkdir -p $(BINDIR)
	$(CXX) $(CXXFLAGS) -o $@ $^

$(OBJDIR)/%.o: $(SRCDIR)/%.cpp
	@mkdir -p $(OBJDIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

test: $(TEST_OBJS) $(OBJS)
	@mkdir -p $(TESTDIR)
	$(CXX) $(CXXFLAGS) -o $(BINDIR)/test $(TEST_OBJS) $(OBJS)
	$(BINDIR)/test

$(OBJDIR)/%.o: $(TESTDIR)/%.cpp $(INCDIR)/%.h
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -rf $(OBJDIR)/*.o $(BINDIR)/Poker $(BINDIR)/test

.PHONY: all clean distclean test doc
















