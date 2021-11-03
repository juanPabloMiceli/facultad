#include <iostream>
#include "pca.h"
#include "eigen.h"
#include "fstream"
#include "chrono"
#include <iomanip>

using namespace std;


PCA::PCA(unsigned int n_components) : _n_components(n_components), _M(), _autovectoresM(), _autovaloresM(){}

void PCA::fit(Matrix X){
    cout<<"\n\nEmpiezo a fitear\n\n";
    auto start = chrono::steady_clock::now();
    int x_rows = X.rows();
    int x_cols = X.cols();
    Vector mus=Vector::Zero(x_cols);
    for (int i = 0; i < x_rows; ++i) {
        mus += X.row(i).transpose();
    }
    mus/=x_rows;
    double den= sqrt(x_rows-1);
    for (int j = 0; j < x_rows; ++j) {
        X.row(j)-=mus.transpose();
    }
    X/=den;
    _M=X.transpose()*X;

    auto end = chrono::steady_clock::now();
    cout<<"\n\nYa tengo la matriz para sacar los autovalores, tarde "<< chrono::duration<double>(end-start).count()<<" segundos.\n\n";

    pair<Vector, Matrix> pi=get_first_eigenvalues(_M, _n_components);
    _autovectoresM=get<1>(pi);
    _autovaloresM=get<0>(pi);
    cout<<"\nTerminamos de fittear PCA\n";
}
double PCA::var_perc(int new_n_comp) {
    if (_autovaloresM.size()==0){
        return -1;
    }else{
        int acum=0;
        for (int i = 0; i < new_n_comp; ++i) {
            acum+=_autovaloresM[i];
        }
        return acum/_autovaloresM.sum();
    }

}



MatrixXd PCA::transform(Matrix X){
    MatrixXd res(X.rows(), _n_components);
    cout<<"\nEmpezamos a transformar PCA\n";
    res = X*_autovectoresM;
    cout<<"\nTerminamos de transformar PCA\n";
    return res;
}

MatrixXd PCA::custom_transform(Matrix X, int alfa){
    if(alfa > int(_n_components)){
        cout<<"\n\nEstas queriendo que calcule un alfa custom ("<<alfa<<") mayor al alfa total ("<<_n_components<<")\n\n";
        assert(false);
    }
    MatrixXd res(X.rows(), alfa);
    cout<<"\nEmpezamos a transformar PCA\n";
    res = X*_autovectoresM.block(0,0,X.cols(),alfa);
    cout<<"\nTerminamos de transformar PCA\n";
    return res;
}


void PCA::read_csv(const string &path){
    /*
     * Leo esto:
     * |        k       |          n        |vacio|...|vacio|
     * |   eigenV0[0]   |  eigenV1[0]       |....|eigenVn[0]|
     * |   eigenV0[1]   |  eigenV1[1]       |....|eigenVn[1]|
     * ......................................................
     * |   eigenV0[k]   |  eigenV1[k]       |....|eigenVn[k]|
     *
     * Este csv no tiene ningun string
     * */

    ifstream csv_in;
    csv_in.open(path);

    int rows, cols;

    if(csv_in.is_open()){

        string line, colname;

        getline(csv_in, line);
        stringstream ss(line);
        ss >> rows;
        if(ss.peek() == ',') ss.ignore();
        ss >> cols;

        Matrix new_pca = Matrix(rows, cols);

        int index=0;
        while(getline(csv_in, line)){
            double val;
            int col = 0;
            while(ss >> val){
                new_pca(index,col) = val;
                if(ss.peek() == ',') ss.ignore();
                col++;
            }
            index++;
        }

        _autovectoresM = new_pca;
        csv_in.close();
    }else{
        cout<<"\n\nNo pude abrir el csv\n\n";
        assert(false);
    }
}


void PCA::write_csv(const string &path){
    /*
     * Escribo esto:
     * |        k       |          n        |vacio|...|vacio|
     * |   eigenV0[0]   |  eigenV1[0]       |....|eigenVn[0]|
     * |   eigenV0[1]   |  eigenV1[1]       |....|eigenVn[1]|
     * ......................................................
     * |   eigenV0[k]   |  eigenV1[k]       |....|eigenVn[k]|
     *
     * Este csv no tiene ningun string
     * */

    ofstream csv_out;
    csv_out.open(path);
    int ev_rows = _autovectoresM.rows();
    int ev_cols = _autovectoresM.cols();

    if(csv_out.is_open()){
        //Paso las filas y las columnas en la primer fila
        csv_out<<ev_rows<<","<<ev_cols<<"\n";

        //Escribo todos los autovectores uno a uno
        for(int i = 0; i < ev_rows; i++){
            for (int j = 0; j < ev_cols; ++j) {
                double valor = _autovectoresM(i,j);
                csv_out<< std::fixed << std::setprecision(10) << valor;
                if(j != ev_cols-1){
                    csv_out<<",";
                }
            }
            if(i != ev_rows-1){
                csv_out<<"\n";
            }
        }

        csv_out.close();
    }else{
        cout<<"\n\nNo pude abrir el csv\n\n";
        assert(false);
    }
}


void PCA::write_binary(const string &path){
    std::ofstream out(path, std::ios::out | std::ios::binary | std::ios::trunc);
    typename Matrix::Index rows=_autovectoresM.rows(), cols=_autovectoresM.cols();
    out.write((char*) (&rows), sizeof(typename Matrix::Index));
    out.write((char*) (&cols), sizeof(typename Matrix::Index));
    out.write((char*) _autovectoresM.data(), rows*cols*sizeof(typename Matrix::Scalar) );
    out.close();
}

void PCA::read_binary(const string &path){
    std::ifstream in(path, std::ios::in | std::ios::binary);
    typename Matrix::Index rows=0, cols=0;
    in.read((char*) (&rows),sizeof(typename Matrix::Index));
    in.read((char*) (&cols),sizeof(typename Matrix::Index));
    _autovectoresM.resize(rows, cols);
    in.read( (char *) _autovectoresM.data() , rows*cols*sizeof(typename Matrix::Scalar) );
    in.close();
}

MatrixXd PCA::ret_autovect() {
    return _autovectoresM;
}

MatrixXd PCA::ret_autoval() {
    return _autovaloresM;
}