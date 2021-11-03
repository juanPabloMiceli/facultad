//
// Created by juampi on 24/10/20.
//

#include "experimentacion.h"


Vector vector_moda(const Matrix &X){
    int x_rows = X.rows();
    int x_cols = X.cols();
    vector<map<int, int> > frecuencias(x_rows);
    Vector res(x_rows);

    for(int row=0; row<x_rows; row++){
        for (int i = 0; i < x_cols; ++i) {
            if (frecuencias[row].count(X(row,i))){
                frecuencias[row][X(row,i)]++;
            }else{
                frecuencias[row][X(row,i)]=1;
            }
        }
        int label_moda=0;
        int max=0;
        for (pair<int, int> frec: frecuencias[row]) {
            if (get<1>(frec)>max){
                max=get<1>(frec);
                label_moda=get<0>(frec);
            }
        }
        res[row] = label_moda;
    }
    return res;
}

vector<string> all_predictions_labels(int n, int min_k, const string &param){
    vector<string> res(n+1);
    res[0] = "imageId";

    for(int i = 1; i < n+1; i++){
        res[i] = param + ": "+to_string(i+min_k-1);
    }
    return res;
}

vector<int> arange(int low, int high){
    vector<int> res(high-low);

    for(int i = 0; i < high-low; i++){
        res[i] = low+i;
    }
    return res;
}

void matrix2csv(Matrix data, const string &path_out, const vector<string> &labels, const vector<int> &indices){

    ofstream csv_out;
    csv_out.open(path_out);
    if(csv_out.is_open()){
        for(unsigned int i=0; i < labels.size(); i++){
            csv_out << labels[i];
            if(i != labels.size()-1){
                csv_out <<",";
            }
        }
        csv_out << "\n";

        for(unsigned int row=0; row < data.rows(); row++){
            csv_out << indices[row]<<",";
            for(unsigned int col=0; col < data.cols(); col++){
                csv_out << data.row(row)[col];
                if(col != data.cols()-1){
                    csv_out <<",";
                }
            }
            csv_out << "\n";
        }
        csv_out.close();
    }else{
        throw "No pude abrir el csv";

    }

}