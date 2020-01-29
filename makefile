CXX	= clang++
#CXX	= g++
CXXFLAGS	= -std=c++14 -Wall -Wpedantic -Wextra -O2
LIBS	= -L/usr/local/lib/ -I/usr/local/include/ -lglut -lGLU -lGL
BIN_NAME	= NESemu
SRC	= ./src
IDIR	= $(SRC)/include
ODIR	= ./obj
DEPS	= $(wildcard $(IDIR)/*.hpp)
CPP_DIRS	=  $(wildcard $(SRC)/*.cpp) # Get list of .cpp file directories.
CPP_FILES	= $(subst $(SRC)/,,$(CPP_DIRS)) # Strip srings of paths.
OBJ_FILES	= $(patsubst %.cpp,%.o,$(CPP_FILES)) # Replace .cpp with .o.
# Prepend object directory to .o file names.
OBJ	= $(patsubst %,$(ODIR)/%,$(OBJ_FILES))


$(ODIR)/%.o: $(SRC)/%.cpp $(DEPS)
	$(CXX) -c -o $@ $< $(CXXFLAGS)

$(BIN_NAME): $(OBJ)
	$(CXX) -o $@ $^ $(CXXFLAGS) $(LIBS)

.PHONY: clean

# Files with '#' and '~' seem to be left around be emacs >:'^(
clean:
	$(RM) $(BIN_NAME) $(ODIR)/*.o *.core *~ $(SRC)/*~ $(IDIR)/*~ \#*\# $(SRC)/\#*\# $(IDIR)/\#*\#
