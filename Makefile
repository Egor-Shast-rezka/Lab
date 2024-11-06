CXX = g++
CXXFLAGS = -Werror -Wpedantic -Wall -std=c++11

SRC_DIR = src
OBJ_DIR = obj

TARGET = read_BMP

SRC_FILES = $(wildcard $(SRC_DIR)/*.cpp)

OBJ_FILES = $(patsubst $(SRC_DIR)/%.cpp,$(OBJ_DIR)/%.o,$(SRC_FILES))

all: $(TARGET)

$(TARGET): $(OBJ_FILES)
	$(CXX) $(CXXFLAGS) -o $@ $^

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ_DIR)/*.o $(TARGET)

run: $(TARGET)
	./$(TARGET) $(OBJ_DIR)/example.bmp

