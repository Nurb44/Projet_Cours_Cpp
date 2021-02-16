CXX = g++
CXXFLAGS = -Wall -g
EXEC = Knn.exe
SRC = $(./src/*.cpp)
OBJ = $(SRC:.cpp=.o)

all: $(EXEC)

$(EXEC) : $(OBJ)
	$(CXX) -o $(EXEC) $(OBJ)

%.o : %.cpp
	$(CXX) $(CXXFLAGS) $< -o $@
	
clean:
	rm -rf $(OBJ)

distclean: clean
	rm -rf $(EXEC)
