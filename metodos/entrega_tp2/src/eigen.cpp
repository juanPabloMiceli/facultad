#include <algorithm>
#include <chrono>
#include <iostream>
#include "eigen.h"

using namespace std;


pair<double, Vector> power_iteration(const Matrix& X, unsigned  num_iter, double eps){
    Vector b = Vector::Random(X.cols());
    Vector b_old= Vector::Zero(X.cols());
    double eigenvalue;
    for (unsigned i = 0; i < num_iter; ++i) {
        b_old=b;
        b= X*b;
        b=b/b.norm();
        if ((b-b_old).lpNorm<1>()<eps) {
            break;
        }
    }
    eigenvalue=b.transpose()*X*b;
    eigenvalue=eigenvalue/b.squaredNorm();

    return make_pair(eigenvalue, b / b.norm());
}

void deflacion(Matrix& X, const Vector& v1, double eigenvalue){
    Matrix prod_ext= eigenvalue* v1 * v1.transpose();
    X=X-prod_ext;
}

pair<Vector, Matrix> get_first_eigenvalues(const Matrix& X, unsigned  num, unsigned  num_iter, double epsilon)
{

    Matrix A(X);
    Vector eigvalues(num);
    Matrix eigvectors(num,A.rows());
    for (unsigned i = 0; i < num; ++i) {
        auto start = chrono::steady_clock::now();

        pair<double, Vector> pi = power_iteration(A, num_iter, epsilon);
        deflacion(A, get<1>(pi), get<0>(pi));
        eigvalues(i)=get<0>(pi);
        eigvectors.row(i) = get<1>(pi);
        cout<<"Conseguimos el autovalor "<<i+1<<"\n";
        auto end = chrono::steady_clock::now();
        cout << "Tiempo por dato: " << chrono::duration_cast<chrono::seconds>(end - start).count() << "segundos\n\n";
    }
    return make_pair(eigvalues, eigvectors.transpose());
}
