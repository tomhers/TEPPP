#include "../include/funcs.h"

using namespace std;

int main(int argc, char *argv[])
{

    int num_chains = stoi(argv[3]);
    int chain_length = stoi(argv[2]);
    double box_dim;
    if (argc >= 5) box_dim = stod(argv[4]);
    else box_dim = 0;
    int num;
    double **coords;
    if (box_dim == 0) {
        coords = read_coords(argv[1], &num);
    } else {
        coords = read_coords(argv[1], &num, chain_length, box_dim);
    }
    double result[num_chains][num_chains];
    ofstream outfile;
    int count = 0;
    double sum = 0;
    outfile.open("lkout.txt");

    for (int i = 0; i < num_chains; i++) {
        result[i][i] = 0;
        double **chain1 = new double*[chain_length];
        for (int j = 0; j < chain_length; j++) {
            chain1[j] = new double[3];
            chain1[j][0] = coords[j + (i * chain_length)][0];
            chain1[j][1] = coords[j + (i * chain_length)][1];
            chain1[j][2] = coords[j + (i * chain_length)][2];
            /*if (j > 0) {
                chain1[j][0] = unwrap(coords[j + (i * chain_length)][0], coords[j - 1 + (i * chain_length)][0], box_dim);
                chain1[j][1] = unwrap(coords[j + (i * chain_length)][1], coords[j - 1 + (i * chain_length)][1], box_dim);
                chain1[j][2] = unwrap(coords[j + (i * chain_length)][2], coords[j - 1 + (i * chain_length)][2], box_dim);
            } else {
                chain1[j][0] = coords[j + (i * chain_length)][0];
                chain1[j][1] = coords[j + (i * chain_length)][1];
                chain1[j][2] = coords[j + (i * chain_length)][2];
            }*/
            
        }

        for (int j = i + 1 ; j < num_chains; j++) {
            double **chain2 = new double*[chain_length];
            for (int k = 0; k < chain_length; k++) {
                chain2[k] = new double[3];
                chain2[k][0] = coords[k + (j * chain_length)][0];
                chain2[k][1] = coords[k + (j * chain_length)][1];
                chain2[k][2] = coords[k + (j * chain_length)][2];
                /*if (k > 0) {
                    chain2[k][0] = unwrap(coords[k + (j * chain_length)][0], coords[k - 1 + (j * chain_length)][0], box_dim);
                    chain2[k][1] = unwrap(coords[k + (j * chain_length)][1], coords[k - 1 + (j * chain_length)][1], box_dim);
                    chain2[k][2] = unwrap(coords[k + (j * chain_length)][2], coords[k - 1 + (j * chain_length)][2], box_dim);
                } else {
                    chain2[k][0] = coords[k + (j * chain_length)][0];
                    chain2[k][1] = coords[k + (j * chain_length)][1];
                    chain2[k][2] = coords[k + (j * chain_length)][2];
                }*/
            }

            double res = lk(chain1, chain2, chain_length, chain_length, false);
            outfile << "linking number between chains " << i << " and " << j << ": " << res << "\n";
            if (i == 6 && j == 28) {
                cout << "linking number between chains " << i << " and " << j << ": " << res << "\n";
                cout << "[";
                for (int z = 0; z < chain_length; z++) {
                    cout << "[" << chain1[z][0] << ", " << chain1[z][1] << ", " << chain1[z][2] << "], ";
                }
                cout << "]\n\n";
                cout << "[";
                for (int z = 0; z < chain_length; z++) {
                    cout << "[" << chain2[z][0] << ", " << chain2[z][1] << ", " << chain2[z][2] << "], ";
                }
                cout << "]\n\n";
            }

            /*if (i == 66 && j == 82) {
                cout << "[";
                for (int z = 0; z < chain_length; z++) {
                    cout << "[" << chain1[z][0] << ", " << chain1[z][1] << ", " << chain1[z][2] << "], ";
                }
                cout << "]\n\n";
                cout << "[";
                for (int z = 0; z < chain_length; z++) {
                    cout << "[" << chain2[z][0] << ", " << chain2[z][1] << ", " << chain2[z][2] << "], ";
                }
                cout << "]\n\n";
            }*/
            result[i][j] = res;
            result[j][i] = res;
            sum += abs(res);
            count++;
            delete_array(chain2, chain_length);
        }

        delete_array(chain1, chain_length);
    }

    delete_array(coords, num_chains);
    outfile.close();
    //cout << "Absolute avg lk: " << sum / count << "\n";

    return 0;

}