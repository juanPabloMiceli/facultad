//
// Created by juampi on 14/10/20.
//

#include "data.h"



Data::Data(string &path, bool has_label, int n_imagenes,float train_percentage) : _path(path), _has_label(has_label), _n_imagenes(n_imagenes), _train_percentage(train_percentage){
    int rows = 0;
    int cols = 0;

    get_rows_and_cols(_path, rows, cols);

    int training_rows = (int)((float)(rows)*_train_percentage);

    Matrix data(rows, cols);
    Matrix labels(rows, 1);
    fill_matrices(data, labels);


    _train_data = data.block(0,0, training_rows, cols);
    _train_labels = labels.block(0,0,training_rows, 1);


    _test_data = data.block(training_rows,0, rows-training_rows, cols);
    _test_labels = labels.block(training_rows,0,rows-training_rows, 1);
    cout<<"\nTerminamos de leer la data\n";

}

double Data::sum_test(){
    return _test_data.sum();
}

double Data::sum_test_l(){
    return _test_labels.sum();
}

double Data::sum_data(){
    return _train_data.sum();
}

double Data::sum_data_l(){
    return _train_labels.sum();
}

void Data::fill_row(Matrix &data, int index, string &line){
    stringstream ss(line);
    int val;
    int col = 0;
    if(_has_label){
        ss >> val;
        if(ss.peek() == ',') ss.ignore();
    }
    while(ss >> val){
        // Add the current integer to the 'colIdx' column's values vector
        data.row(index)(col) = val;

        // If the next token is a comma, ignore it and move on
        if(ss.peek() == ',') ss.ignore();

        // Increment the column index
        col++;
    }
}

void Data::fill_matrices(Matrix &data, Matrix &labels){
    ifstream file;
    file.open(_path);
    if(file.is_open()){
        string line, colname;
        getline(file, line);
        int index = 0;
        while(getline(file, line) && index < data.rows()){
            stringstream ss(line);
            if(_has_label){
                getline(ss, colname, ',');
                labels(index) = stoi(colname); //Le resto el ascii
            }
            fill_row(data, index, line);

            index++;
        }

        file.close();

    }else{
        cout<<"\n\nNo encontre el archivo de training\n\n";
        assert(false);
    }


}


int Data::get_cols(const string &line){
    int cols = 0;
    for(char c : line){
        if(c==','){
            cols++;
        }
    }
    if(!_has_label){
        cols++;
    }
    return cols;
}

void Data::get_rows_and_cols(const string &path, int &rows, int &cols){
    ifstream file;
    file.open(path);
    if(file.is_open()){
        string line;
        getline(file, line);
        cols = get_cols(line);
        while(getline(file, line)){
            rows++;
            if(_n_imagenes != -1 && _n_imagenes <= rows){
                break;
            }
        }
        file.close();

    }else{
        cout<<"\n\nNo encontre el archivo de training\n\n";
        assert(false);
    }


}

float Data::get_train_percentage() {
    return _train_percentage;
}
