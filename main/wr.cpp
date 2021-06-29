#include "../include/funcs.h"

using namespace std;

int main(int argc, char *argv[])
{

    int num_chains = stoi(argv[3]);
    int chain_length = stoi(argv[2]);
    double box_dim;
    if (argc >= 5) box_dim = 2 * stod(argv[4]);
    else box_dim = 0;
    int num;
    double **coords = read_coords(argv[1], &num);
    double result[num_chains];
    ofstream outfile;
    int count = 0;
    double sum = 0;
    outfile.open("wrout.txt");

    for (int i = 0; i < num_chains; i++) {
        double **chain1 = new double*[chain_length];
        for (int j = 0; j < chain_length; j++) {
            chain1[j] = new double[3];
            if (j > 0 && box_dim != 0) {
                chain1[j][0] = unwrap(chain1[j - 1][0], coords[j + (i * chain_length)][0], box_dim);
                chain1[j][1] = unwrap(chain1[j - 1][1], coords[j + (i * chain_length)][1], box_dim);
                chain1[j][2] = unwrap(chain1[j - 1][2], coords[j + (i * chain_length)][2], box_dim);
            } else {
                chain1[j][0] = coords[j + (i * chain_length)][0];
                chain1[j][1] = coords[j + (i * chain_length)][1];
                chain1[j][2] = coords[j + (i * chain_length)][2];
            }
        }

        double res = wr(chain1, chain_length, false);
        outfile << "writhe of chain " << i <<  ": " << res << "\n";
        if (i == 2) {
            cout << "writhe of chain " << i <<  ": " << res << "\n";
            cout << "[";
            for (int z = 0; z < chain_length; z++) {
                cout << "[" << chain1[z][0] << ", " << chain1[z][1] << ", " << chain1[z][2] << "], ";
            }
            cout << "]\n\n";
        }
        result[i] = res;
        sum += abs(res);
        count++;
        delete_array(chain1, chain_length);
    }

    delete_array(coords, num_chains);
    outfile.close();
    cout << "Absolute avg wr: " << sum / count << "\n";

    return 0;

}