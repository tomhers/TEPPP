#################################################################
########################   MakeVars   ###########################
#################################################################

#CXX=g++

CXX_OPT= -g -I "./include" -Wall -Wextra -O2

LD_LIB=

LD_OPT=

MKDIR=mkdir -p ./obj

TARGET=read_dcd

SRC=$(wildcard ./dcd/*.cpp)

OBJ=$(patsubst ./dcd/%.cpp,./obj/%.o,$(SRC))

#################################################################
#################################################################

all:$(TARGET)
	@echo "Compilation Success"

$(TARGET):Makefile

./obj/%.o:./dcd/%.cpp
	@$(MKDIR)
	$(CXX) $(CXX_OPT) -c $< -o $@

$(TARGET):$(OBJ)
	$(CXX) $(CXX_OPT) $(LD_LIB) $(OBJ) -o $@ $(LD_OPT)

clean:
	rm -f $(TARGET) ./obj/*.o
