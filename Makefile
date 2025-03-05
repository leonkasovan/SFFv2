CXX = g++
CXXFLAGS = -I./ -Wall -Wextra -std=c++11
SRC = $(wildcard *.cpp) $(wildcard utiltype/*.cpp) $(wildcard encoding/*.cpp) $(wildcard encoding/LZ5/*.cpp)
OBJ = $(SRC:.cpp=.o)
TARGET = sff2_app

all: $(TARGET)

$(TARGET): $(OBJ)
	$(CXX) -o $@ $^

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ) $(TARGET)