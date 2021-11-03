//
// Created by juampi on 24/10/20.
//

#ifndef TP2_EXPERIMENTACION_H
#define TP2_EXPERIMENTACION_H


#include "pca.h"
#include "eigen.h"
#include "fstream"
#include "types.h"

using namespace std;

Vector vector_moda(const Matrix &X);
vector<string> all_predictions_labels(int n, int min_k, const string &param);
vector<int> arange(int low, int high);
void matrix2csv(Matrix data, const string &path_out, const vector<string> &labels, const vector<int> &indices);



#endif //TP2_EXPERIMENTACION_H
