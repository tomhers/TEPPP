# The Topological Entanglement of Polymers, Proteins, and Periodic systems (TEPPP) Software

TEPPP is a software package designed to aid in the calculation of several topological entanglement values in molecular systems. It is designed to work both in serial and in parallel when coupled with a functioning MPI installation.

## Getting Started

### Building

TEPPP requires a compiler which fully supports C++17 (GCC 7 and up). If parallel execution is desired, a functioning MPI installation must be present in the PATH variable. To build only the serial version of the software, run the following command: `make serial`. To build only the parallel version of the software, run the following command: `make mpi`. To make both versions of the software, type the following command: `make all`.

### Usage

The current version of TEPPP only supports running individual commands through the command line to obtain the desired results. If the coordinates of the system to be analyzed are in a file with an extension other than .tepp, they must be converted into a file readable by TEPPP. To do this, run the following command in the top-level installation directory: `./convertor "/path/to/filename.ext"`. Note that only .read_data, .dump, and .dcd files are supported at this time. Once the convertor command has been run, the file with the converted data will be located in the `TEPPP/converted` directory for further use.

Once a .tepp file with the desired coordinates has been generated, any of the software commands can be used in conjunction with the file to generate results. The `base` commands that are currently available are:

* jones | Calculates the Jones polynomial of each chain in the system
* lk | Calculates the linking number between each pair of chains in the system
* wr | Calculates the Writhe of each chain in the system

All `base` commands are called using the same syntax. There are three required parameters, which must be provided in the command line in the order shown below:

1. The filename (including path) of the data file containing the coordinates of the system to analyze.
2. The length of each chain within the provided system.
3. The number of chains within the provided system.

There is also an optional fourth parameter which should be used if the coordinates in the data file have been wrapped using periodic conditions. In this case, the fourth parameter should be the size of the periodic box used to perform the wrapping.

In addition to these `base` commands, there are several types of variant commands also included in TEPPP. `periodic` commands analyze the topological entanglement of a given system while accounting for periodic boundary conditions. The `periodic` commands that are currently available are:

* periodic_wr | Calculates the periodic Writhe of each chain in the system
* periodic_lk | Calculates the periodic linking number between each pair of chains in the system

The syntax for calling `periodic` commands is very similar to calling base commands; the only difference is that the fourth parameter is required instead of optional. Thus, calling `periodic` commands requires four parameters, which must be provided in the command line in the order shown below:

1. The filename (including path) of the data file containing the coordinates of the system to analyze.
2. The length of each chain within the provided system.
3. The number of chains within the provided system.
4. The length of one side of the periodic box.

`scan` commands are used to analyze the topological entanglement of certain parts of chains rather than the entire chain. For example, if a user wants to the part of a single chain that contributes the most to the overall Writhe of that chain, they would use a `scan` command. The `scan` commands that are currently available are:

* jones_scan | Calculates the Jones polynomial along each chain at given intervals
* lk_scan | Calculates the linking number along each pair of chains at given intervals
* wr_scan | Calculates the Writhe along each chain at given intervals
* periodic_lk_scan | Calculates the periodic linking number along each pair of chains at given intervals
* periodic_wr_scan | Calculates the periodic Writhe along each chain at given intervals

Calling `scan` commands requires six parameters, which must be provided in the command line in the order shown below:

1. The filename (including path) of the data file containing the coordinates of the system to analyze.
2. The length of each chain within the provided system.
3. The number of chains within the provided system.
4. The length of the initial interval at which to scan.
5. The length of the final interval at which to scan.
6. The amount to increment the interval after a scan completes.

There is also an optional seventh parameter which should be used if the coordinates in the data file have been wrapped using periodic conditions. In this case, the seventh parameter should be the size of the periodic box used to perform the wrapping. Additionally, there is an optional parameter that can passed only to the `jones_scan` command. The user may scan for a specific knot type in order to find the location of a knot within a chain by passing the name of the knot to `jones_scan` in the command line. Currently, the only supported knot types are trefoil, figure-8, pentafoil, and stevedore.

`mpi` commands are parallel versions of the `base`, `periodic`, and `scan` commands discussed above. They leverage MPI to split the workload between a given number of processors rather than performing the work serially. The `mpi` commands that are currently available are:

* jones_mpi | Calculates the Jones polynomial of each chain in the system in parallel
* lk_mpi | Calculates the linking number between each pair of chains in the system in parallel
* wr_mpi | Calculates the Writhe of each chain in the system in parallel
* periodic_wr_mpi | Calculates the periodic Writhe of each chain in the system in parallel
* periodic_lk_mpi | Calculates the periodic linking number between each pair of chains in the system in parallel
* jones_scan_mpi | Calculates the Jones polynomial along each chain at given intervals in parallel
* lk_scan_mpi | Calculates the linking number along each pair of chains at given intervals in parallel
* wr_scan_mpi | Calculates the Writhe along each chain at given intervals in parallel
* periodic_wr_scan_mpi | Calculates the periodic Writhe along each chain at given intervals in parallel

`mpi` commands have the same syntax as their `base`, `periodic`, and `scan` counterparts but must be called using `mpirun` rather than running the command itself.

### Examples

To calculate the linking numbers between each pair of chains in a system found in "../data/systemA.tepp" with 100 chains each of length 20:

`./lk "../data/systemA.tepp" 20 100`

To calculate the periodic Writhe of each chain in a system found in "../data/systemB.tepp" with 50 chains each of length 25 and a periodic box with length 9.275:

`./periodic_wr "../data/systemB.tepp" 25 50 9.275`

To scan along each chain and calculate the Jones polynomial of each subset of each chain from size 10 to size 20, skipping by 2, and searching for a trefoil knot in a system found in "../data/systemC.tepp" with 10 chains each of length 200:

`./jones_scan "../data/systemC.tepp" 200 10 10 20 2 "trefoil"`

To calculate the linking number between each pair of chains in a system found in "../data/systemD.tepp" with 20 chains each of length 20, using MPI to split the work between 4 different processes:

`mpirun -np 4 ./lk_mpi "../data/systemD.tepp" 20 20`

