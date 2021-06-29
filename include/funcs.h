#ifndef FUNCS_H
#define FUNCS_H

#include <iostream>
#include <stdio.h>
#include <cmath>
#include <random>
#include <string>
#include <string.h>
#include <map>
#include <vector>
#include <algorithm>
#include <stdlib.h>
#include <sstream>
#include <fstream>

using namespace std;

struct proj_coords {
    vector<vector<double>> coords;
    vector<vector<double>> proj;
    vector<vector<int>> crossings;
    bool success;
};

typedef struct proj_coords Struct;

map<int, double> dims_map = {
    { 20, 6.676575 },
    { 30, 7.6427684 },
    { 40, 8.4119549 },
    { 50, 9.061505 },
    { 100, 11.41678 },
    { 200, 14.38424 },
    { 300, 16.465845 },
    { 400, 18.12301 }
};

void delete_array(double **arr, int size);
void delete_array(int **arr, int size);
void normalize3(const double *v, double *ans);
void cross3(const double *v1, const double *v2, double *ans);
void sub3(const double *v1, const double *v2, double *ans);

bool on_segment(double *p, double *q, double *r);
bool intersect(double *p1, double *q1, double *p2, double *q2);
bool are_collinear(vector<double> p1, vector<double> p2, vector<double> p3, vector<double> p4);
bool intersect1(vector<double> p0, vector<double> p1, vector<double> p2, vector<double> p3, double *rx, double *ry);
bool has_mult_crossings(vector<vector<int>> crossings);

int orientation(double *p, double *q, double *r);
int count_loops(vector<vector<int>> neigh_array, int n);

double distance(vector<double> p1, vector<double> p2);
double compute_one(vector<double> p1, vector<double> p2, vector<double> p3, vector<double> p4);
double dot3(const double *v1, const double *v2);
double wr(double **chain, int length, bool is_closed);
double lk(double **chain1, double **chain2, int length1, int length2, bool is_closed, double offx = 0, double offy = 0, double offz = 0);

double *get_random_proj();
vector<double> unwrap(vector<double> p1, vector<double> p2, double box_dim);
vector<double> get_intersection(vector<double> p0, vector<double> p1, vector<double> p2, vector<double> p3);
map<int, double> mult_poly(int power);
map<int, double> simple_mult(map<int, double> a, map<int, double> b);

vector<vector<int>> generate_neigh_array(int n, bool closed);
vector<vector<int>> compute_img(double **coords, int n, vector<double> box_dims);
vector<vector<int>> count_crossings(vector<vector<int>> neigh_array, vector<vector<double>> proj, int n, bool count_all);
vector<vector<int>> reduce_crossings(vector<vector<int>> initial_crossings, vector<vector<double>> coords);

double **get_two_vec(const double *proj);
double **generate_random_walk(int n);
double **read_coords(string fname, int *n);
double **read_coords(string fname, int *n, int chain_length, double box_dim);
vector<vector<double>> get_proj(vector<vector<double>> coords, int n);

Struct next_mult_crossings(vector<vector<double>> proj, vector<vector<double>> coords, vector<vector<int>> neigh_array, int n, bool is_closed);

/**
 * Delete 2D array of doubles
 * 
 * @param arr Array of doubles to delete
 * @param size Number of elements in array
 * 
 */
void delete_array(double **arr, int size)
{

    for (int i = 0; i < size; i++) {
        delete [] arr[i];
    }
    delete [] arr;

}

/**
 * Delete 2D array of ints
 * 
 * @param arr Array of ints to delete
 * @param size Number of elements in array
 * 
 */
void delete_array(int **arr, int size)
{

    for (int i = 0; i < size; i++) {
        delete [] arr[i];
    }
    delete [] arr;

}

/**
 * Normalize a 3D vector
 * 
 * @param[in] v The vector to normalize
 * @param[out] ans The normalized vector
 */
void normalize3(const double *v, double *ans)
{
  double scale = 1.0/sqrt(v[0]*v[0]+v[1]*v[1]+v[2]*v[2]);
  ans[0] = v[0]*scale;
  ans[1] = v[1]*scale;
  ans[2] = v[2]*scale;
}

/**
 * Get the cross product between two 3D vectors
 * 
 * @param[in] v1 The first vector in the calculation
 * @param[in] v2 The second vector in the calculation
 * @param[out] ans The cross product of v1 and v2
 */
void cross3(const double *v1, const double *v2, double *ans)
{
  ans[0] = v1[1]*v2[2] - v1[2]*v2[1];
  ans[1] = v1[2]*v2[0] - v1[0]*v2[2];
  ans[2] = v1[0]*v2[1] - v1[1]*v2[0];
}

/**
 * Get the difference between two 3D vectors
 * 
 * @param[in] v1 The first vector in the calculation
 * @param[in] v2 The second vector in the calculation
 * @param[out] ans The difference of v1 and v2
 */
void sub3(const double *v1, const double *v2, double *ans)
{
  ans[0] = v1[0] - v2[0];
  ans[1] = v1[1] - v2[1];
  ans[2] = v1[2] - v2[2];
}

/**
 * Check if 4 3D points are collinear
 * 
 * @param p1, p2, p3, p4 Points to check for collinearity
 * @return true if points are collinear, false if points are not collinear
 */
bool are_collinear(vector<double> p1, vector<double> p2, vector<double> p3, vector<double> p4)
{

    vector<double> v1 = {p2[0] - p1[0], p2[1] - p1[1]};
    vector<double> v2 = {p4[0] - p3[0], p4[1] - p3[1]};
    double cross = v1[0] * v2[1] - v2[0] * v1[1];

    if (abs(cross) < 0.001) return true;
    else return false;

}

/**
 * Check if two edges in 3-space intersect
 * 
 * @param[in] p0, p1 Points that form the first edge
 * @param[in] p2, p3 Points that form the second edge
 * @param[out] rx, ry Coordinates of intersection point if the edges intersect
 * @return true if edges intersect, false if edges do not intersect
 */
bool intersect1(vector<double> p0, vector<double> p1, vector<double> p2, vector<double> p3, double *rx, double *ry)
{

    if (are_collinear(p0, p1, p2, p3)) return false;
    double s1_x, s1_y, s2_x, s2_y;
    s1_x = p1[0] - p0[0];
    s1_y = p1[1] - p0[1];
    s2_x = p3[0] - p2[0];
    s2_y = p3[1] - p2[1];

    double det = -s2_x * s1_y + s1_x * s2_y;
    if (abs(det) < 0.0001) return false;
    double s, t;
    s = (-s1_y * (p0[0] - p2[0]) + s1_x * (p0[1] - p2[1])) / det;
    t = (s2_x * (p0[1] - p2[1]) - s2_y * (p0[0] - p2[0])) / det;

    if (s >= 0 && s <= 1 && t >= 0 && t <= 1) {
        if (rx != NULL) {
            *rx = p0[0] + (t * s1_x);
        }

        if (ry != NULL) {
            *ry = p0[1] + (t * s1_y);
        }
        
        return true;
    }

    return false;

}

/**
 * Checks if there is an edge that intersects with more than one other edge
 * 
 * @param crossings 
 */
bool has_mult_crossings(vector<vector<int>> crossings)
{

    map<int, bool> found;
    for (int i = 0; i < crossings.size(); i++) {
        if (found.find(crossings[i][0]) != found.end() || found.find(crossings[i][2]) != found.end()) return true;
        found[crossings[i][0]] = true;
        found[crossings[i][2]] = true;
    }
    
    return false;

}

int orientation(double *p, double *q, double *r)
{

  double val = (q[1] - p[1]) * (r[0] - q[0]) - (q[0] - p[0]) * (r[1] - q[1]);
  if (val == 0) return 0;

  return (val > 0)? 1: 2;

}

int count_loops(vector<vector<int>> neigh_array, int n)
{

    bool found[n] = {false};
    int count = 0;
    int loops = 0;
    for (int i = 0; i < n; i++) {
        if (found[i]) continue;
        found[i] = true;
        int curr = i;
        while (1) {
            found[curr] = true;
            if (neigh_array[curr][0] >= 0 && !found[neigh_array[curr][0]]) {
                int temp = neigh_array[curr][0];
                curr = temp;
            } else if (neigh_array[curr][1] >= 0 && !found[neigh_array[curr][1]]) {
                int temp = neigh_array[curr][1];
                curr = temp;
            } else {
                loops++;
                break;
            }
        }
    }

    return loops;

}

double distance(vector<double> p1, vector<double> p2)
{

    return sqrt(pow(p2[0]-p1[0], 2) + pow(p2[1]-p1[1], 2));

}

double compute_one(vector<double> p1, vector<double> p2, vector<double> p3, vector<double> p4)
{

    double a1 [3];
    double a2 [3];
    double b1 [3];
    double b2 [3];
    double c1 [3];
    double sum;
    double ra [3];
    double rb [3];
    double r00 [3];
    double r01 [3];
    double r10 [3];
    double r11 [3];
    double v1 [3];
    double v2 [3];
    double v3 [3];
    double v4 [3];
    double u1 [3];
    double u2 [3];
    double u3 [3];
    double u4 [3];
    double d1;
    double d2;
    double d3;
    double d4;
    double as1;
    double as2;
    double as3;
    double as4;
    double aux1 [3];
    double aux;
    double alk;
    double norm;
    double sign;
    double pi = 2 * asin(1.0);

    a1[0]=p1[0];
    a1[1]=p1[1];
    a1[2]=p1[2];
    a2[0]=p2[0];
    a2[1]=p2[1];
    a2[2]=p2[2];
    b1[0]=p3[0];
    b1[1]=p3[1];
    b1[2]=p3[2];
    b2[0]=p4[0];
    b2[1]=p4[1];
    b2[2]=p4[2];
    sub3(a2, a1, ra);
    sub3(b2, b1, rb);
    sub3(a1, b1, r00);
    sub3(a1, b2, r01);
    sub3(a2, b1, r10);
    sub3(a2, b2, r11);
    cross3(r00, r01, v1);
    normalize3(v1, u1);
    cross3(r01, r11, v2);
    normalize3(v2, u2);
    cross3(r11, r10, v3);
    normalize3(v3, u3);
    cross3(r10, r00, v4);
    normalize3(v4, u4);
    d1=dot3(u1, u2);
    d2=dot3(u2, u3);
    d3=dot3(u3, u4);
    d4=dot3(u4, u1);
    as1=asin(d1);
    as2=asin(d2);
    as3=asin(d3);
    as4=asin(d4);
    cross3(ra, rb, aux1);
    aux=dot3(aux1, r00);
    if (aux<0) {alk=-1*((as1+as2+as3+as4)/(4*pi));}
    else {alk=(as1+as2+as3+as4)/(4*pi);}
    if (alk != alk) return 0;
    else return alk;

}

double dot3(const double *v1, const double *v2)
{
  return v1[0]*v2[0]+v1[1]*v2[1]+v1[2]*v2[2];
}

double wr(double **chain, int length, bool is_closed)
{

    double result = 0;
    double pi = 2 * asin(1.0);

    for (int i=0; i<length-2; i++)
    {
        vector<double> p1, p2;
        if (i+1==length) {
            if (!is_closed) continue;
            p1.push_back(chain[i][0]);
            p1.push_back(chain[i][1]);
            p1.push_back(chain[i][2]);
            p2.push_back(chain[0][0]);
            p2.push_back(chain[0][1]);
            p2.push_back(chain[0][2]);
            //continue;
        } else {
            p1.push_back(chain[i][0]);
            p1.push_back(chain[i][1]);
            p1.push_back(chain[i][2]);
            p2.push_back(chain[i+1][0]);
            p2.push_back(chain[i+1][1]);
            p2.push_back(chain[i+1][2]);
        }
        for (int j=i+2; j<length; j++)
        {
            vector<double> p3, p4;
            if (j+1==length) {
                if (!is_closed) continue;
                p3.push_back(chain[j][0]);
                p3.push_back(chain[j][1]);
                p3.push_back(chain[j][2]);
                p4.push_back(chain[0][0]);
                p4.push_back(chain[0][1]);
                p4.push_back(chain[0][2]);
                //continue;
            }

            else {
                p3.push_back(chain[j][0]);
                p3.push_back(chain[j][1]);
                p3.push_back(chain[j][2]);
                p4.push_back(chain[j+1][0]);
                p4.push_back(chain[j+1][1]);
                p4.push_back(chain[j+1][2]);
            }

            result += compute_one(p1, p2, p3, p4);

        }
    }

    return result * 2;

}

double lk(double **chain1, double **chain2, int length1, int length2, bool is_closed, double offx /*= 0*/, double offy /*= 0*/, double offz /*= 0*/)
{

    vector<double> p1, p2, p3, p4;
    double result = 0;
    double pi = 2 * asin(1.0);

    for (int i=0; i<length1; i++)
    {
        vector<double> p1, p2;
        if (i+1==length1) {
            if (!is_closed) continue;
            p1.push_back(chain1[i][0]);
            p1.push_back(chain1[i][1]);
            p1.push_back(chain1[i][2]);
            p2.push_back(chain1[0][0]);
            p2.push_back(chain1[0][1]);
            p2.push_back(chain1[0][2]);
            //continue;
        } else {
            p1.push_back(chain1[i][0]);
            p1.push_back(chain1[i][1]);
            p1.push_back(chain1[i][2]);
            p2.push_back(chain1[i+1][0]);
            p2.push_back(chain1[i+1][1]);
            p2.push_back(chain1[i+1][2]);
        }
        for (int j=0; j<length2; j++)
        {
            vector<double> p3, p4;
            if (j+1==length2) {
                if (!is_closed) continue;
                p3.push_back(chain2[j][0]+offx);
                p3.push_back(chain2[j][1]+offy);
                p3.push_back(chain2[j][2]+offz);
                p4.push_back(chain2[0][0]+offx);
                p4.push_back(chain2[0][1]+offy);
                p4.push_back(chain2[0][2]+offz);
                //continue;
            }

            else {
                p3.push_back(chain2[j][0]+offx);
                p3.push_back(chain2[j][1]+offy);
                p3.push_back(chain2[j][2]+offz);
                p4.push_back(chain2[j+1][0]+offx);
                p4.push_back(chain2[j+1][1]+offy);
                p4.push_back(chain2[j+1][2]+offz);
            }

            result += compute_one(p1, p2, p3, p4);

        }
    }

    return result;

}

double *get_random_proj()
{

    random_device random_device;
    mt19937 random_engine(random_device());
    uniform_real_distribution<double> dist(0.0, 1.0);
    double b[3];
    double b1[3];
    double *result;
    result = new double[3];
    double sum = 0;
    while (sum > 1 || sum < 0.0001) {
        b[0] = 2 * dist(random_engine) - 1;
        b[1] = 2 * dist(random_engine) - 1;
        b[2] = 2 * dist(random_engine) - 1;
        b1[0] = b[0] * b[0];
        b1[1] = b[1] * b[1];
        b1[2] = b[2] * b[2];
        sum = b1[0] + b1[1] + b1[2];
    }

    result[0] = b1[0] / sqrt(sum);
    result[1] = b1[1] / sqrt(sum);
    result[2] = b1[2] / sqrt(sum);
    return result;

}

vector<double> unwrap(vector<double> p1, vector<double> p2, double box_dim)
{
    int imgx = round((p1[0] - p2[0]) / box_dim);
    int imgy = round((p1[1] - p2[1]) / box_dim);
    int imgz = round((p1[2] - p2[2]) / box_dim);

    return {p2[0] + (imgx * box_dim), p2[1] + (imgy * box_dim), p2[2] + (imgz * box_dim)};
}

vector<double> get_intersection(vector<double> p0, vector<double> p1, vector<double> p2, vector<double> p3)
{

    double s1_x, s1_y, s2_x, s2_y, det, t;
    s1_x = p1[0] - p0[0];
    s1_y = p1[1] - p0[1];
    s2_x = p3[0] - p2[0];
    s2_y = p3[1] - p2[1];
    det = -s2_x * s1_y + s1_x * s2_y;
    t = (s2_x * (p0[1] - p2[1]) - s2_y * (p0[0] - p2[0])) / det;
    vector<double> result = {p0[0] + (t * s1_x), p0[1] + (t * s1_y)};
    return result;

}

map<int, double> mult_poly(int power)
{

    map<int, double> base;
    base[-2] = -1;
    base[2] = -1;
    if (power == 2) {
        return base;
    }

    map<int, double> result;
    map<int, double> temp;
    temp[-2] = -1;
    temp[2] = -1;
    for (int k = 2; k < power; k++) {
        for (auto const& x : temp) {
            for (auto const& y : base) {
                result[x.first + y.first] += x.second * y.second;
            }
        }
        temp = result;
        result.clear();
    }

    return temp;

}

map<int, double> simple_mult(map<int, double> a, map<int, double> b)
{

    map<int, double> result;
    for (auto const& x : a) {
        for (auto const& y : b) {
            result[x.first + y.first] += x.second * y.second;
        }
    }

    return result;

}

vector<vector<int>> generate_neigh_array(int n, bool closed)
{
    vector<vector<int>> neigh_array;
    for (int i = 1; i < n - 1; i++) {
        neigh_array.push_back({i-1, i+1});
    }

    if (closed) {
        neigh_array.push_back({n-2, 0});
        neigh_array.insert(neigh_array.begin(), {n-1, 1});
    } else {
        neigh_array.push_back({n-2, -1});
        neigh_array.insert(neigh_array.begin(), {-1, 1});
    }

    return neigh_array;
}

vector<vector<int>> compute_img(double **coords, int n, vector<double> box_dims)
{

    vector<vector<int>> result;
    for (int i = 0; i < n; i++) {
        int ximg = round(coords[i][0] / (2 * box_dims[0]));
        int yimg = round(coords[i][1] / (2 * box_dims[1]));
        int zimg = round(coords[i][2] / (2 * box_dims[2]));
        vector<int> temp = {ximg, yimg, zimg};
        bool found = false;
        for (auto vec : result) {
            if (vec == temp) {
                found = true;
                break;
            }
        }
        if (!found) {
            result.push_back(temp);
        }
    }

    return result;

}

vector<vector<int>> count_crossings(vector<vector<int>> neigh_array, vector<vector<double>> proj, int n, bool count_all)
{

    int count = 0;
    vector<vector<int>> res;
    int lasti, lastj;
    if (count_all) lasti = n;
    else lasti = n - 2;
    map<int, vector<vector<int>>> order;
    map<int, vector<double>> distances;
    
    for (int i = 0; i < lasti; i++) {
        if (neigh_array[i][1] < 0) continue;
        if (count_all) lastj = n + i;
        else lastj = n;
        for (int j = i+2; j < lastj; j++) {
            int p2 = j % n;
            if (abs(i - p2) < 2) continue;
            if (i == neigh_array[p2][1]) continue;
            if (neigh_array[i][1] == p2) continue;
            if (neigh_array[p2][1] < 0) continue;
            double rx = 1;
            double ry = 1;
            if (intersect1(proj[i], proj[neigh_array[i][1]], proj[p2], proj[neigh_array[p2][1]], &rx, &ry)) {
                double dist = distance(proj[i], {rx, ry});
                if (order.find(i) == order.end()) {
                    order[i].push_back({i, neigh_array[i][1], p2, neigh_array[p2][1]});
                    distances[i].push_back(dist);
                } else {
                    bool found = false;
                    for (int z = 0; z < order[i].size(); z++) {
                        if (dist < distances[i][z]) {
                            order[i].insert(order[i].begin()+z, {i, neigh_array[i][1], p2, neigh_array[p2][1]});
                            distances[i].insert(distances[i].begin() + z, dist);
                            found = true;
                            break;
                        }
                    }
                    if (!found) {
                        order[i].push_back({i, neigh_array[i][1], p2, neigh_array[p2][1]});
                        distances[i].push_back(dist);
                    }
                }
                if (i == neigh_array[p2][1]) continue;
                if (neigh_array[i][1] == p2) continue;
            } 
        }
    }
    for (auto it = order.begin(); it != order.end(); it++) {
        int i = it->first;
        for (int j = 0; j < order[i].size(); j++) {
            res.push_back(order[i][j]);
        }
    }

    return res;

}

vector<vector<int>> reduce_crossings(vector<vector<int>> initial_crossings, vector<vector<double>> coords)
{

    int init_crossings = initial_crossings.size();
    map<int, int> crossing_map;
    for (int i = 0; i < init_crossings; i++) {
        crossing_map[initial_crossings[i][0]] = initial_crossings[i][1];
        crossing_map[initial_crossings[i][2]] = initial_crossings[i][3];
    }
    vector<vector<int>> temp_result;
    vector<int> remove_crossings;
    int count = 0;
    bool boolarray[init_crossings];
    for (int i = 0; i < init_crossings; i++) {
        boolarray[i] = true;
    }
    int p11, p12, p13, p14, p21, p22, p23, p24, p31, p32, p33, p34;
    for (int i = 0; i < initial_crossings.size(); i++) {
        bool found = false;
        if (find(remove_crossings.begin(), remove_crossings.end(), i) != remove_crossings.end()) continue;
        p11 = initial_crossings[i][0];
        p12 = initial_crossings[i][1];
        p13 = initial_crossings[i][2];
        p14 = initial_crossings[i][3];
        if (found) continue;
        double wr1 = compute_one(coords[initial_crossings[i][0]], coords[initial_crossings[i][1]], coords[initial_crossings[i][2]], coords[initial_crossings[i][3]]);
        for (int j = i + 1; j < initial_crossings.size(); j++) {
            found = false;
            if (find(remove_crossings.begin(), remove_crossings.end(), j) != remove_crossings.end()) continue;
            if (found) continue;
            double wr2 = compute_one(coords[initial_crossings[j][0]], coords[initial_crossings[j][1]], coords[initial_crossings[j][2]], coords[initial_crossings[j][3]]);
            if ((wr1 < 0 && wr2 < 0) || wr1 > 0 && wr2 > 0) found = true;
            if (found) continue;
            p21 = initial_crossings[j][0];
            p22 = initial_crossings[j][1];
            p23 = initial_crossings[j][2];
            p24 = initial_crossings[j][3];
            if (p12 == p21 && (p14 == p23 || p24 == p13)) {
                remove_crossings.push_back(i);
                remove_crossings.push_back(j);
                j = initial_crossings.size();
                continue;
            }
            if (found) continue;
        }
    }

    for (int i = remove_crossings.size() - 1; i >= 0; i--) {
        initial_crossings.erase(initial_crossings.begin() + remove_crossings[i]);
    }
    remove_crossings.clear();
    int p1, p2, p3, p4;
    for (int i = 0; i < initial_crossings.size(); i++) {
        bool found = false;
        p1 = initial_crossings[i][0];
        p2 = initial_crossings[i][1];
        p3 = initial_crossings[i][2];
        p4 = initial_crossings[i][3];
        if (p2 == 0) p2 += coords.size();
        if (p4 == 0) p4 += coords.size();
        for (int j = min(p2, p3); j < max(p2, p3); j++) {
            if (crossing_map.find(j) != crossing_map.end()) {
                found = true;
                break;
            }
            if (found) continue;
        }
        if (!found) {
            remove_crossings.push_back(i);
            crossing_map.erase(initial_crossings[i][0]);
            crossing_map.erase(initial_crossings[i][2]);
        }
    }
    
    sort(remove_crossings.begin(), remove_crossings.end());
    for (int i = remove_crossings.size() - 1; i >= 0; i--) {
        initial_crossings.erase(initial_crossings.begin() + remove_crossings[i]);
    }

    count = 0;
    vector<vector<int>> result;
    for (int i = 0; i < initial_crossings.size(); i++) {
        result.push_back({initial_crossings[i][0], initial_crossings[i][1], initial_crossings[i][2], initial_crossings[i][3]});
    }

    return result;

}

double **get_two_vec(const double *proj)
{
    random_device random_device;
    mt19937 random_engine(random_device());
    normal_distribution<double> dist(0.0, 1.0);
    double a[3] = {0, 0, 0};
    double b[3];
    double **result;
    result = new double*[2];
    result[0] = new double[3];
    result[1] = new double[3];
    double a1[3];
    double a2[3];
    double proj1[3];
    double sum = 0;
    double sum1, sum2;
    while (sum < 0.0001) {
        a[0] = dist(random_engine);
        a[1] = dist(random_engine);
        a[2] = dist(random_engine);
        a1[0] = a[0] * proj[0];
        a1[1] = a[1] * proj[1];
        a1[2] = a[2] * proj[2];
        sum1 = a1[0] + a1[1] + a1[2];
        a2[0] = proj[0] * proj[0];
        a2[1] = proj[1] * proj[1];
        a2[2] = proj[2] * proj[2];
        sum2 = a2[0] + a2[1] + a2[2];
        proj1[0] = proj[0] * sum1 * (1/sum2);
        proj1[1] = proj[1] * sum1 * (1/sum2);
        proj1[2] = proj[2] * sum1 * (1/sum2);
        a[0] = a[0] - proj1[0];
        a[1] = a[1] - proj1[1];
        a[2] = a[2] - proj1[2];
        a1[0] = a[0] * a[0];
        a1[1] = a[1] * a[1];
        a1[2] = a[2] * a[2];
        sum = a1[0] + a1[1] + a1[2];
    }

    result[0][0] = a[0] / sqrt(sum);
    result[0][1] = a[1] / sqrt(sum);
    result[0][2] = a[2] / sqrt(sum);
    result[1][0] = result[0][1] * proj[2] - result[0][2] * proj[1];
    result[1][1] = -(result[0][0] * proj[2] - result[0][2] * proj[0]);
    result[1][2] = result[0][0] * proj[1] - result[0][1] * proj[0];

    return result;
}

double **generate_random_walk(int n)
{

    double **result = new double*[n];
    for (int i = 0; i < n; i++) {
        result[i] = new double[3];
    }

    random_device random_device;
    mt19937 random_engine(random_device());
    uniform_real_distribution<double> dist(0.0, 1.0);
    double pi = 2 * asin(1.0);
    for (int i = 0; i < n; i++) {
        double u = dist(random_engine);
        double v = dist(random_engine);
        double theta = 2 * pi * u;
        double phi = pi * v;
        if (i == 0) {
            result[i][0] = cos(theta) * sin(phi);
            result[i][1] = sin(theta) * sin(phi);
            result[i][2] = cos(phi);
            cout << result[i][0] << ", " << result[i][1] << ", " << result[i][2] << "\n";
        } else {
            result[i][0] = result[i-1][0] + (cos(theta) * sin(phi));
            result[i][1] = result[i-1][1] + (sin(theta) * sin(phi));
            result[i][2] = result[i-1][2] + cos(phi);
            cout << result[i][0] << ", " << result[i][1] << ", " << result[i][2] << "\n";
        }
    }
    
    return result;
}

double **read_coords(string fname, int *n)
{

    string line;
    ifstream myfile;
    myfile.open(fname);
    int num_atoms = 0;
    string::size_type sz;
    vector<vector<double>> temp;

    if (!myfile.is_open()) {
        cout << "Couldn't open file\n";
        exit(EXIT_FAILURE);
    }

    while (getline(myfile, line)) {
        string buf;
        stringstream ss(line);
        int count = 0;
        vector<string> tokens;
        while (ss >> buf) {
            tokens.push_back(buf);
            count++;
        }

        if (count > 0) {
            temp.push_back({stod(tokens[0], &sz), stod(tokens[1], &sz), stod(tokens[2], &sz)});
        }
    }
    
    double **result = new double*[temp.size()];
    for (int i = 0; i < temp.size(); i++) {
        result[i] = temp[i].data();
    }
    
    *n = temp.size();
    return result;
}

double **read_coords(string fname, int *n, int chain_length, double box_dim)
{
    string line;
    ifstream myfile;
    myfile.open(fname);
    int num_atoms = 0;
    string::size_type sz;
    vector<vector<double>> temp;

    if (!myfile.is_open()) {
        cout << "Couldn't open file\n";
        exit(EXIT_FAILURE);
    }

    while (getline(myfile, line)) {
        string buf;
        stringstream ss(line);
        int count = 0;
        vector<string> tokens;
        while (ss >> buf) {
            tokens.push_back(buf);
            count++;
        }

        if (count > 0) {
            if (temp.size() == 0 || (temp.size() % chain_length) == 0) {
                temp.push_back({stod(tokens[0], &sz), stod(tokens[1], &sz), stod(tokens[2], &sz)});
            } else {
                temp.push_back(unwrap(temp[temp.size() - 1], {stod(tokens[0], &sz), stod(tokens[1], &sz), stod(tokens[2], &sz)}, box_dim));
            }
        }
    }
    
    double **result = new double*[temp.size()];
    for (int i = 0; i < temp.size(); i++) {
        result[i] = temp[i].data();
    }
    
    *n = temp.size();
    return result;
}

vector<vector<double>> get_proj(vector<vector<double>> coords, int n)
{

    vector<vector<double>> result;
    double **temp = new double*[n];
    for (int i = 0; i < n; i++) {
        temp[i] = new double[2];
        temp[i][0] = temp[i][1] = 0;
    }
    double *proj_vector = get_random_proj();
    double **xy = get_two_vec(proj_vector);
    double stack[3][2];
    stack[0][0] = xy[0][0];
    stack[0][1] = xy[1][0];
    stack[1][0] = xy[0][1];
    stack[1][1] = xy[1][1];
    stack[2][0] = xy[0][2];
    stack[2][1] = xy[1][2];

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < 2; j++) {
            for (int k = 0; k < 3; k++) {
                temp[i][j] += coords[i][k] * stack[k][j];
            }
        }
    }

    for (int i = 0; i < n; i++) {
        result.push_back({temp[i][0], temp[i][1]});
    }
    delete [] proj_vector;
    delete_array(xy, 2);
    delete_array(temp, n);
    return result;

}

Struct next_mult_crossings(vector<vector<double>> proj, vector<vector<double>> coords, vector<vector<int>> neigh_array, int n, bool is_closed)
{

    int last = -1;
    int off = 0;
    int last_off = 0;
    int temp_off;
    map<int, int> offmap;
    map<int, int> same_crossing;
    map<int, vector<vector<double>>> crossings;
    vector<vector<int>> before_cross = count_crossings(neigh_array, proj, proj.size(), true);
    for (int i = 0; i < before_cross.size(); i++) {
        for (int j = i+1; j < before_cross.size(); j++) {
            if (before_cross[i][0] == before_cross[j][2] && before_cross[j][0] == before_cross[i][2]) {
                same_crossing[i] = j;
            }
        }
    }
    for (int i = 0; i < before_cross.size(); i++) {
        vector<double> temp = get_intersection(proj[before_cross[i][0]], proj[before_cross[i][1]], proj[before_cross[i][2]], proj[before_cross[i][3]]);
        if (before_cross[i][0] < before_cross[i][2]) {
            crossings[before_cross[i][0]].push_back(temp);
            crossings[before_cross[i][2]].push_back(temp);
        }
        if (before_cross[i][0] == last) {
            temp_off++;
            before_cross[i][0] += temp_off;
            before_cross[i][1] += temp_off;
            off++;
            offmap[i] = last_off;
        } else {
            last = before_cross[i][0];
            last_off = off;
            offmap[i] = off;
            temp_off = 0;
        }
        if (before_cross[i][0] - temp_off == proj.size() - 1) before_cross[i][1] += proj.size();
    }
    for (int i = 0; i < before_cross.size(); i++) {
        before_cross[i][0] = (before_cross[i][0] + offmap[i]) % (proj.size() + off);
        before_cross[i][1] = (before_cross[i][1] + offmap[i]) % (proj.size() + off);
    }
    vector<vector<int>> new_cross;
    for (auto it = same_crossing.begin(); it != same_crossing.end(); it++) {
        new_cross.push_back({before_cross[it->first][0], before_cross[it->first][1], before_cross[it->second][0], before_cross[it->second][1]});
    }
    
    vector<vector<double>> new_proj = proj;
    vector<vector<double>> new_coords = coords;
    vector<int> offset_vec;
    vector<vector<double>> org_crossings;
    int offset = 0;

    vector<vector<int>> final_cross;
    offset = 0;
    int num_above_one = 0;
    bool found_above_four = false;
    if (num_above_one > crossings.size() / 4 || found_above_four) {
        Struct error;
        error.success = false;
        cout << "too many multiple crossing edges\n";
        return error;
    }
    
    int num_above_thres = 0;
    for (auto it = crossings.begin(); it != crossings.end(); it++) {
        int i = it->first;
        if (crossings[i].size() >= 2) {
            if (crossings[i].size() > 2) num_above_thres++;
            for (int j = 0; j < crossings[i].size() - 1; j++) {
                auto iter = new_proj.begin() + i + offset + 1;
                auto coords_iter = new_coords.begin() + i + offset + 1;
                int next_p = i + 1;
                if (i + 1 == n && neigh_array[i][1] == -1) continue;
                if (i + 1 == n) next_p = 0;
                double newx = crossings[i][j][0] + ((crossings[i][j+1][0] - crossings[i][j][0]) / 2);
                double newy = crossings[i][j][1] + ((crossings[i][j+1][1] - crossings[i][j][1]) / 2);
                double newx_coords = coords[i][0] + (j+1) * ((coords[next_p][0] - coords[i][0]) / crossings[i].size());
                double newy_coords = coords[i][1] + (j+1) * ((coords[next_p][1] - coords[i][1]) / crossings[i].size());
                double newz_coords = coords[i][2] + (j+1) * ((coords[next_p][2] - coords[i][2]) / crossings[i].size());
                if (proj[i].size() == 2) {
                    new_proj.insert(iter, {newx, newy});
                    new_coords.insert(coords_iter, {newx_coords, newy_coords, newz_coords});
                    offset++;
                } else {
                    double t = (newx - proj[i][0]) / (proj[next_p][0] - proj[i][0]);
                    double newz = proj[i][2] + ((proj[next_p][2] - proj[i][2]) * t);
                    new_proj.insert(iter, {newx, newy, newz});
                    new_coords.insert(coords_iter, {newx_coords, newy_coords, newz_coords});
                    offset++;
                }
            }
        }
    }

    Struct final;
    final.coords = new_coords;
    final.proj = new_proj;
    final.crossings = new_cross;
    final.success = true;
    return final;

}

#endif