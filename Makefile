#################################################################
########################   MakeVars   ###########################
#################################################################

CXX=g++

MPICXX=mpic++

CXX_OPT= -g -I "./include" -Wall -Wextra -O2 -std=c++17

LD_LIB=

LD_OPT=

MKDIR=mkdir -p ./obj

TARGET=convertor jones jones_scan lk lk_scan periodic_lk periodic_lk_scan periodic_wr periodic_wr_scan wr wr_scan jones_mpi lk_mpi lk_scan_mpi periodic_lk_mpi periodic_wr_mpi periodic_wr_scan_mpi wr_mpi wr_scan_mpi

DCD_TARGET=convertor

TEMP_TARGET=convertor jones

SERIAL_TARGET=convertor jones jones_scan lk lk_scan periodic_lk periodic_lk_scan periodic_wr periodic_wr_scan wr wr_scan

MPI_TARGET=convertor jones_mpi lk_mpi lk_scan_mpi periodic_lk_mpi periodic_wr_mpi periodic_wr_scan_mpi wr_mpi wr_scan_mpi

SRC=$(wildcard ./dcd/*.cpp)

OBJ=$(patsubst ./dcd/%.cpp,./obj/%.o,$(SRC))

#################################################################
#################################################################

all:$(TARGET)
	@echo "Compilation Success"

serial:$(SERIAL_TARGET)
	@echo "Serial Compilation Success"

mpi:$(MPI_TARGET)
	@echo "Parallel Compilation Success"

$(DCD_TARGET):Makefile

./obj/%.o:./dcd/%.cpp
	@$(MKDIR)
	$(CXX) $(CXX_OPT) -c $< -o $@

$(DCD_TARGET):$(OBJ)
	$(CXX) $(CXX_OPT) $(LD_LIB) $(OBJ) -o $@ $(LD_OPT)
jones:main/jones.cpp
	$(CXX) $? -o main/$@
jones_scan:main/jones_scan.cpp
	$(CXX) $? -o main/$@
lk:main/lk.cpp
	$(CXX) $? -o main/$@
lk_scan:main/lk_scan.cpp
	$(CXX) $? -o main/$@
periodic_lk:main/periodic_lk.cpp
	$(CXX) $? -o main/$@
periodic_lk_scan:main/periodic_lk_scan.cpp
	$(CXX) $? -o main/$@
periodic_wr:main/periodic_wr.cpp
	$(CXX) $? -o main/$@
periodic_wr_scan:main/periodic_wr_scan.cpp
	$(CXX) $? -o main/$@
wr:main/wr.cpp
	$(CXX) $? -o main/$@
wr_scan:main/wr_scan.cpp
	$(CXX) $? -o main/$@
jones_mpi:main/jones_mpi.cpp
	$(MPICXX) $? -o main/$@
lk_mpi:main/lk_mpi.cpp
	$(MPICXX) $? -o main/$@
lk_scan_mpi:main/lk_scan_mpi.cpp
	$(MPICXX) $? -o main/$@
periodic_lk_mpi:main/periodic_lk_mpi.cpp
	$(MPICXX) $? -o main/$@
periodic_wr_mpi:main/periodic_wr_mpi.cpp
	$(MPICXX) $? -o main/$@
periodic_wr_scan_mpi:main/periodic_wr_scan_mpi.cpp
	$(MPICXX) $? -o main/$@
wr_mpi:main/wr_mpi.cpp
	$(MPICXX) $? -o main/$@
wr_scan_mpi:main/wr_scan_mpi.cpp
	$(MPICXX) $? -o main/$@

clean:
	rm -f $(TARGET) ./obj/*.o
