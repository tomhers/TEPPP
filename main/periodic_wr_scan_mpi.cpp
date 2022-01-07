#include "../include/funcs.h"
#include "mpi.h"

using namespace std;

double periodic_wr(double** coords, int chain_length, vector<double> box_dims, bool is_closed)
{
	double result = 0;
	vector<vector<int>> images = compute_img(coords, chain_length, box_dims);
	for (int i = 0; i < images.size(); i++)
	{
		if (images[i][0] == 0 && images[i][1] == 0 && images[i][2] == 0)
			continue;
		for (int j = 0; j < chain_length; j++)
		{
			vector<double> p1 = {coords[j][0], coords[j][1], coords[j][2]};
			vector<double> p2;
			if (j + 1 < chain_length)
			{
				p2.push_back(coords[j + 1][0]);
				p2.push_back(coords[j + 1][1]);
				p2.push_back(coords[j + 1][2]);
			}
			else if (j + 1 == chain_length && is_closed)
			{
				p2.push_back(coords[0][0]);
				p2.push_back(coords[0][1]);
				p2.push_back(coords[0][2]);
			}
			else
				continue;
			for (int k = 0; k < chain_length; k++)
			{
				double deltax = images[i][0] * box_dims[0];
				double deltay = images[i][1] * box_dims[1];
				double deltaz = images[i][2] * box_dims[2];
				vector<double> p3 = {coords[k][0] + deltax, coords[k][1] + deltay, coords[k][2] + deltaz};
				vector<double> p4;
				if (k + 1 < chain_length)
				{
					p4.push_back(coords[k + 1][0] + deltax);
					p4.push_back(coords[k + 1][1] + deltay);
					p4.push_back(coords[k + 1][2] + deltaz);
				}
				else if (k + 1 == chain_length && is_closed)
				{
					p4.push_back(coords[0][0] + deltax);
					p4.push_back(coords[0][1] + deltay);
					p4.push_back(coords[0][2] + deltaz);
				}
				else
					continue;

				result += compute_one(p1, p2, p3, p4);
			}
		}
	}

	return result;
}

int main(int argc, char* argv[])
{
	if (argc < 7)
	{
		cout << "Not enough parameters! Exiting...\n";
		return 0;
	}

	MPI_Init(&argc, &argv);
	int rank, size;
	MPI_Comm_size(MPI_COMM_WORLD, &size);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);

	int chain_length = stoi(argv[2]);
	int num_chains = stoi(argv[3]);
	int start_chunk = stoi(argv[4]);
	int end_chunk = stoi(argv[5]);
	int step = stoi(argv[6]);
	int chunk = num_chains / size;
	int num;
	double box_dim;
	if (argc >= 8)
		box_dim = stod(argv[7]);
	else
		box_dim = 0;
	vector<double> box_dims = {box_dim, box_dim, box_dim};
	ofstream outfile;
	string fname = to_string(chain_length) + "periodic_wrmpiout" + to_string(rank) + ".txt";
	outfile.open(fname);
	double** coords = read_coords(argv[1], &num);
	for (int i = rank * chunk; i < (rank + 1) * chunk; i++)
	{
		double** temp_coords = new double*[chain_length];
		for (int j = 0; j < chain_length; j++)
		{
			temp_coords[j] = new double[3];
			temp_coords[j][0] = coords[(i * chain_length) + j][0];
			temp_coords[j][1] = coords[(i * chain_length) + j][1];
			temp_coords[j][2] = coords[(i * chain_length) + j][2];
			// cout << temp_coords[j][0] << ", " << temp_coords[j][1] << ", " << temp_coords[j][2] <<
			// "\n";
		}

		for (int a = start_chunk; a <= end_chunk; a += step)
		{
			double** temp_chain1 = new double*[a];
			for (int b = 0; b < a; b++)
			{
				temp_chain1[b] = new double[3];
			}

			for (int b = 0; b < chain_length - a; b++)
			{
				for (int c = 0; c < a; c++)
				{
					temp_chain1[c][0] = temp_coords[b + c][0];
					temp_chain1[c][1] = temp_coords[b + c][1];
					temp_chain1[c][2] = temp_coords[b + c][2];
				}

				double res = periodic_wr(temp_chain1, a, box_dims, false);
				outfile << "periodic writhe of chain " << i << " at atom " << b << " with chunk length " << a << ": "
						<< res << "\n";
			}

			delete_array(temp_chain1, a);
		}

		delete_array(temp_coords, chain_length);
	}

	outfile.close();
	delete_array(coords, num_chains);

	return 0;
}