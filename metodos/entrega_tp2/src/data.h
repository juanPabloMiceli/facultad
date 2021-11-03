//
// Created by juampi on 14/10/20.
//

#ifndef TP2_DATA_H
#define TP2_DATA_H

#pragma once

#include "types.h"
#include "fstream"
#include "string.h"
#include "iostream"

using namespace std;

class Data {
public:
    Data(string &path, bool has_label, int n_imagenes, float train_percentage);
    float get_train_percentage();
    MatrixXd _train_data;
    MatrixXd _test_data;
    MatrixXd _train_labels;
    MatrixXd _test_labels;
    double sum_test();
    double sum_test_l();
    double sum_data();
    double sum_data_l();


private:
    string _path;
    bool _has_label;
    int _n_imagenes;
    float _train_percentage;
    int get_cols(const string &line);
    void get_rows_and_cols(const string &path, int &rows, int &cols);
    void fill_matrices(Matrix &data, Matrix &labels);

    void fill_row(Matrix &data, int index, string &line);
};

#endif //TP2_DATA_H
