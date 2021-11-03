#pragma once

#include <Eigen/Sparse>
#include <Eigen/Dense>

using Eigen::MatrixXd;

typedef Eigen::Matrix<double, Eigen::Dynamic, Eigen::Dynamic, Eigen::RowMajor> Matrix;
typedef Eigen::SparseMatrix<double> SparseMatrix;

typedef Eigen::VectorXd Vector;
typedef Eigen::Matrix<std::pair<double, int>, Eigen::Dynamic, 1> tuple_vector;

typedef struct config_t {
    int metodo;
    std::string path_train;
    std::string path_test;
    std::string path_pca_in;
    std::string path_out;
    std::string path_out2;

    int n_imagenes;
    int min_k, max_k;
    int min_alfa, max_alfa;

    float train_percentage;

    int k_neighbors, pca_alfa;

} config_t;