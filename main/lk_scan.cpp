#include "../include/funcs.h"

using namespace std;

int main(int argc, char *argv[])
{

    if (argc < 7) {
        cout << "Not enough parameters! Exiting...\n";
        return 0;
    }

    int chain_length = stoi(argv[2]);
    int num_chains = stoi(argv[3]);
    int start_chunk = stoi(argv[4]);
    int end_chunk = stoi(argv[5]);
    int step = stoi(argv[6]);
    int num;
    double **coords = read_coords(argv[1], &num);
    ofstream outfile;
    outfile.open("lkscanout.txt");

    for (int i = 0; i < num_chains; i++) {
        double **chain1 = new double*[chain_length];
        for (int j = 0; j < chain_length; j++) {
            chain1[j] = new double[3];
            chain1[j][0] = coords[j + (i * chain_length)][0];
            chain1[j][1] = coords[j + (i * chain_length)][1];
            chain1[j][2] = coords[j + (i * chain_length)][2];
        }

        for (int j = i + 1 ; j < num_chains; j++) {
            double **chain2 = new double*[chain_length];
            for (int k = 0; k < chain_length; k++) {
                chain2[k] = new double[3];
                chain2[k][0] = coords[k + (j * chain_length)][0];
                chain2[k][1] = coords[k + (j * chain_length)][1];
                chain2[k][2] = coords[k + (j * chain_length)][2];
            }

            for (int a = 10; a <= chain_length; a+=5) {
                double **temp_chain1 = new double*[a];
                for (int b = 0; b < a; b++) {
                    temp_chain1[b] = new double[3];
                }
                for (int b = 0; b < chain_length - a; b++) {
                    for (int c = 0; c < a; c++) {
                        temp_chain1[c][0] = chain1[b+c][0];
                        temp_chain1[c][1] = chain1[b+c][1];
                        temp_chain1[c][2] = chain1[b+c][2];
                    }

                    double **temp_chain2 = new double*[a];
                    for (int e = 0; e < a; e++) {
                        temp_chain2[e] = new double[3];
                    }
                    for (int e = 0; e < chain_length - a; e++) {
                        for (int f = 0; f < a; f++) {
                            temp_chain2[f][0] = chain2[e+f][0];
                            temp_chain2[f][1] = chain2[e+f][1];
                            temp_chain2[f][2] = chain2[e+f][2];
                        }

                        double res = lk(temp_chain1, temp_chain2, a, a, false);
                        outfile << "linking number between chains " << i << " starting at atom " << b << " and " << j << " starting at atom " << e << " with chunk length " << a << ": " << res << "\n";

                    }

                    delete_array(temp_chain2, a);
                }

                delete_array(temp_chain1, a);
            }

            delete_array(chain2, chain_length);
        }

        delete_array(chain1, chain_length);
    }

    delete_array(coords, num_chains);
    outfile.close();

    return 0;

}