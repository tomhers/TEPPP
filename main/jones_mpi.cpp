#include "../include/funcs.h"
#include "mpi.h"

using namespace std;

int main(int argc, char *argv[])
{

    MPI_Init(&argc, &argv);
    int rank, size;
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    int chain_length = 100;
    int num_chains = 4;
    int chunk = num_chains / size;
    int offset = chunk * rank;
    bool last = false;
    if (rank + 1 == size) last = true;
    int num;
    map<int, double> result;
    string indir = "../data/" + string(argv[2]);
    string infile = indir + string(argv[1]);
    cout << "infile: " << infile << "\n";
    string outdir = "../results/" + string(argv[2]);
    string outfile_name = outdir + to_string(rank) + "_out" + string(argv[1]);
    ofstream outfile;
    outfile.open(outfile_name);
    double **coords = read_coords(infile, &num);
    for (int i = rank * chunk; i < (rank + 1) * chunk; i++) {
        double **temp_coords = new double*[chain_length];
        for (int j = 0; j < chain_length; j++) {
            temp_coords[j] = new double[3];
            temp_coords[j][0] = coords[(i * chain_length) + j][0];
            temp_coords[j][1] = coords[(i * chain_length) + j][1];
            temp_coords[j][2] = coords[(i * chain_length) + j][2];
            //cout << temp_coords[j][0] << ", " << temp_coords[j][1] << ", " << temp_coords[j][2] << "\n";
        }
        map<int, double> jones_poly = jones("", temp_coords, true, chain_length, 25);
        outfile << "Chain " << i << " jones: ";
        for (map<int, double>::const_iterator it = jones_poly.begin(); it != jones_poly.end(); ++it) {
            outfile << it->second << "A^" << it->first << " + ";
            result[it->first] += it->second;
        }
        outfile << "\n";
        delete_array(temp_coords, chain_length);
    }

    outfile << "Total system jones: ";
    for (map<int, double>::const_iterator it = result.begin(); it != result.end(); ++it) {
        if (it->second == 0 || it->second == -0) continue;
        outfile << it->second << "A^" << it->first << " + ";
    }
    outfile << "\n";
    //int temp = jones("2_input.read_data");
    //int temp = jones_rw(3, 100, 100);
    //double *scanned = scan(argv[1], num_chains, chain_length, chunk, last, rank);
    //cout << "max contribution: " << scanned[0] << "\n";
    //cout << "first atom of max contributor: " << scanned[1] << "\n";
    //cout << "length of max contributor: " << scanned[2] << "\n";
    //cout << "average writhe: " << scanned[3] << "\n";
    //double res = simple_wr(100, 1000, "oakridgedata/SNAPSHOTS-sorted/TREFOIL/sorted.txt");
    //cout << "Rank " << rank << " done\n";
    outfile.close();
    MPI_Finalize();
    return 0;

}
