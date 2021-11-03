#include <algorithm>
//#include <chrono>
#include <iostream>
#include "knn.h"

#include "chrono"

using namespace std;


KNNClassifier::KNNClassifier(unsigned int n_neighbors) : _n_neig(n_neighbors), _data(), _data_rows(), _data_cols(), _data_std_vector(), _labels(){}

void KNNClassifier::set_n_neig(int k) {
    _n_neig = k;
}

void KNNClassifier::fit(Matrix X, Matrix y){
    cout<<"A guardar los labels"<<endl;
    _labels=y;
    cout<<"Labels guardados"<<endl;
    _data=X;
    _data_rows = _data.rows();
    _data_cols = _data.cols();
    _data_std_vector.resize(_data_rows*_data_cols);
    for (int i = 0; i < _data_rows; ++i) {
        for (int j = 0; j < _data_cols; ++j) {
            _data_std_vector[i*_data_cols+j] = _data(i,j);

        }
    }

    cout<<"Data guardada"<<endl;

}

void KNNClassifier:: swap(Vector &s, int i, int j){
    Vector a =s;
    s[i]=s[j];
    s[j]=a[i];
}

int KNNClassifier::findMinPos(const Vector &s, int desde, int hasta){
    int min= desde;
    for (int i = desde+1; i < hasta; ++i) {
        if (s[i]< s[min]){
            min=i;
        }
    }
    return min;
}


void KNNClassifier::ordenar(Vector &s, Vector & labels, int max_k){
    for(int i=0; i < max_k; i++){
        int minPos=findMinPos(s, i, s.size());
        swap(s, i, minPos);
        swap(labels, i, minPos);
    }
}


Vector KNNClassifier :: v_normas (const Vector &dato, int min_k, int max_k){
    Vector training= Vector (_data.rows());
    Vector labels_copy(_labels);


    vector<int> vec(dato.data(), dato.data() + dato.rows() * dato.cols());

    for (int i = 0; i < _data_rows; ++i) {
        double norma = 0.0f;
        for(int j = 0; j < _data_cols; ++j) {
            norma += (_data_std_vector[i*_data_cols+j]-vec[j]) * (_data_std_vector[i*_data_cols+j]-vec[j]);
        }
        training(i) = norma;
    }

    ordenar(training, labels_copy, max_k);
    Vector res = labels_copy.block(min_k-1, 0,max_k - min_k+1,1);
    return res.transpose();
}

int KNNClassifier :: moda (const Vector &labels){
    map<int, int> frecuencias;
    for (int i = 0; i < labels.size(); ++i) {
        if (frecuencias.count(labels[i])){
            frecuencias[labels[i]]++;
        }else{
            frecuencias[labels[i]]=1;
        }
    }
    int label_moda=0;
    int max=0;
    for (pair<int, int> frec: frecuencias) {
        if (get<1>(frec)>max){
            max=get<1>(frec);
            label_moda=get<0>(frec);
        }
    }
    return label_moda;
}


Vector KNNClassifier::predict(Matrix X)
{
    // Creamos vector columna a devolver
    auto ret = Vector(X.rows());
    int x_rows = X.rows();

    for (int dato = 0; dato < x_rows; ++dato) {

        cout<<"\nClasificando el dato "<<dato+1<<"\n";

        Vector labels_vecinos=v_normas(X.row(dato), 1, (int)(_n_neig));
        ret(dato)= moda(labels_vecinos);
    }

    return ret;
}

Matrix KNNClassifier::all_neighbor_matrix(Matrix X, int min_k, int max_k){
    Matrix res = Matrix(X.rows(), max_k - min_k + 1);//_data.rows()

    for (int dato = 0; dato < X.rows(); ++dato) {
        cout<<"Haciendo fila "<<dato<<"\n\n";
        res.row(dato) =v_normas(X.row(dato), min_k, max_k);
    }

    return res;
}