#pragma once
#include "types.h"

class PCA {
public:
    PCA(unsigned int n_components);

    void fit(Matrix X);

    Eigen::MatrixXd transform(Matrix X);
    MatrixXd custom_transform(Matrix X, int alfa);
    double var_perc(int new_n_comp);
    MatrixXd ret_autovect();
    MatrixXd ret_autoval();
    void read_csv(const std::string &path);
    void write_csv(const std::string &path);

    void write_binary(const std::string &path);
    void read_binary(const std::string &path);

private:
    unsigned int _n_components;
    MatrixXd _M;
    MatrixXd _autovectoresM;      //Cada columna es un autovector
    Vector _autovaloresM;
};
