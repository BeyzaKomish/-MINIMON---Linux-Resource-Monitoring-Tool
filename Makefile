CXX = g++
CXXFLAGS = -Wall -std=c++17 -Icore -Iui 

TARGET = minimon

SRC = main.cpp \
	  core/collector.cpp \
	  core/analyzer.cpp \
	  core/reporter.cpp \
	  ui/cli.cpp \

OBJ = $(SRC:.cpp=.o)

all: $(TARGET)

$(TARGET): $(OBJ)
	$(CXX) $(CXXFLAGS) $(OBJ) -o $(TARGET)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ) $(TARGET)