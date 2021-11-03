#pragma once

#include "types.h"



class KNNClassifier {
public:

    explicit KNNClassifier(unsigned int n_neighbors);

    void fit(Matrix X, Matrix y);

    Vector predict(Matrix X);
    void set_n_neig(int k);

    Matrix all_neighbor_matrix(Matrix X, int min_k, int max_k);


private:
    unsigned int _n_neig;
    MatrixXd _data;
    int _data_rows;
    int _data_cols;
    std::vector<int> _data_std_vector;
    MatrixXd _labels;
    void swap(Vector &s, int i, int j);
    int findMinPos(const Vector &s, int desde, int hasta);
    void ordenar(Vector &s, Vector& labels, int max_k);
    Vector v_normas (const Vector &dato, int min_k, int max_k);
    static int moda(const Vector &labels);
};
