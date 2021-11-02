#include <stdlib.h>
#include <iostream>
#include <stdio.h>
#include <vector>
#include <map>
#include <math.h>


using namespace std;



int maximaCantidadFB(vector<int> &w, vector<int> &r, int R);

int maximaCantidadAuxFB(vector<int> &w, vector<int> &r, int indice, int rMin);

int maximaCantidadBT(vector<int> &w, vector<int> &r, int R, bool poda1, bool poda2);

int maximaCantidadAuxBT(vector<int> &w, vector<int> &r, int indice, int rMin, int cantApilados, int &maxActual, bool poda1, bool poda2);

int maximaCantidadPD(vector<int> &w, vector<int> &r, int R);

int maximaCantidadAuxPD(vector<vector<int>> &memo, vector<int> &w, vector<int> &r, int indice, int rMin);

void printVector(vector<int> &v);