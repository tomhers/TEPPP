# The Topological Entanglement of Polymers, Proteins, and Periodic systems (TEPPP) Software

TEPPP is a software package designed to aid in the calculation of several topological entanglement values in molecular systems. It is designed to work both in serial and in parallel when coupled with a functioning MPI installation.

## Getting Started

### Building

TEPPP requires a compiler which fully supports C++17 (GCC 7 and up). If parallel execution is desired, a functioning MPI installation must be present in the PATH variable. To build only the serial version of the software, run the following command: `make serial`. To build only the parallel version of the software, run the following command: `make mpi`. To make both versions of the software, type the following command: `make all`.

### Usage

The current version of TEPPP only supports running individual commands through the command line to obtain the desired results. If the coordinates of the system to be analyzed are in a file with an extension other than .tepp, they must be converted into a file readable by TEPPP. To do this, run the following command in the top-level installation directory: `./convertor "/path/to/filename.fileext`. Note that only .read_data, .dump, and .dcd files are supported at this time. Once the convertor command has been run, the file with the converted data will be located in the `TEPPP/converted` directory for further use.

Once a .tepp file with the desired coordinates has been generated, any of the software commands can be used in conjunction with the file to generate results. The base commands that are currently available are:

* wr | Calculates the Writhe of each chain in the system
* lk | Calculates the linking number between each chain in the system
* jones | Calculates the Jones polynomial of each chain in the system

All base commands are called using the same syntax. There are three required parameters, which must be provided in the command line in the order shown below:

1. The filename (including path) of the data file containing the coordinates of the system to analyze.
2. The length of each chain within the provided system.
3. The number of chains within the provided system.

There is also an optional fourth parameter which should be used if the coordinates in the data file have been wrapped using periodic conditions. In this case, the fourth parameter should be the size of the periodic box used to perform the wrapping.

In addition to these base commands, there are several types of variant commands also included in TEPPP. These commands fall into one of two categories: `scan` commands or `periodic` commands. 