//
// Created by pachi on 5/6/19.
//

#include <iostream>
#include "pca.h"
#include "eigen.h"
#include "knn.h"
#include "data.h"
#include "chrono"
#include "fstream"
#include "tomar_parametros.h"
#include "experimentacion.h"


int main(int argc, char** argv){
    config_t config;
    procesar_opciones(argc, argv, &config);

    chequear_parametros(&config);

    //Podemos hacer esto porque es barato y, en un principio, se usa en todos los metodos
    KNNClassifier clf = KNNClassifier(config.k_neighbors);


    auto start = chrono::steady_clock::now();
    auto end = chrono::steady_clock::now();

    switch(config.metodo){
        case KNN:{
            cout<<"\n\nEmpezamos KNN\n\n";
            start = chrono::steady_clock::now();
            //Levantamos la data
            Data data = Data(config.path_train, true, config.n_imagenes, 1);
            Data test_data = Data(config.path_test, false, -1, 0);

            //Guardamos la data en el clasificador
            clf.fit(data._train_data, data._train_labels);

            //Clasificamos los datos de entrada
            Vector pred = clf.predict(test_data._test_data);

            end = chrono::steady_clock::now();
            cout << "KNN con "<<config.k_neighbors<<" vecinos para "<<data._train_data.rows()<<" datos de entrenamiento y ";
            cout<<test_data._test_data.rows()<<" datos de testing tardo "<< chrono::duration<double>(end - start).count() << " segundos\n\n";


            vector<string> labels = {"ImageId", "Label"};
            vector<int> indices = arange(1, pred.rows()+1);
            matrix2csv(pred, config.path_out, labels, indices);
            break;
        }

        case PCA_KNN:{
            cout<<"\n\nEmpezamos PCA + KNN\n\n";
            start = chrono::steady_clock::now();

            //Levantamos la data
            Data data = Data(config.path_train, true, config.n_imagenes, 1);
            Data test_data = Data(config.path_test, false, -1, 0);

            //Creamos el objeto pca con la cantidad de alfas necesarios
            PCA pca = PCA(config.pca_alfa);


            if(!config.path_pca_in.empty()){
                cout<<"\n\nLevantamos un csv ya existente\n\n";
                pca.read_binary(config.path_pca_in);
            }else{
                cout<<"\n\nTenemos que conseguir pca de cero\n\n";
                pca.fit(data._train_data);
                if(!config.path_out2.empty()){
                    pca.write_binary(config.path_out2);
                }
            }


            //Transformamos los datos de entrada
            Matrix train_pca = pca.transform(data._train_data);
            Matrix test_pca  = pca.transform(test_data._test_data);

            //Hacemos el fit de KNN
            clf.fit(train_pca, data._train_labels);

            //Clasificamos los datos
            Vector pred = clf.predict(test_pca);
            end = chrono::steady_clock::now();
            cout << "PCA+KNN con "<<config.k_neighbors<<" vecinos y "<<train_pca.cols()<<" alfas para "<<data._train_data.rows();
            cout<<" imagenes de train y "<<test_data._test_data.rows()<<" de testing tardo " << chrono::duration<double>(end - start).count() << " segundos\n\n";

            //Guardamos las predicciones en un csv
            vector<string> labels = {"ImageId", "Label"};
            vector<int> indices = arange(1,pred.rows()+1);
            matrix2csv(pred, config.path_out, labels, indices);

            break;
        }
        case PRED_VECINOS: {
            cout<<"\n\nEmpezamos vecinos KNN\n\n";
            Data data = Data(config.path_train, true, config.n_imagenes, config.train_percentage);
            clf.fit(data._train_data, data._train_labels);

            start = chrono::steady_clock::now();
            Matrix all_neighbor = clf.all_neighbor_matrix(data._test_data, config.min_k, config.max_k);
            end = chrono::steady_clock::now();
            cout << "La matriz de all neighbors tardo " << chrono::duration_cast<chrono::seconds>(end - start).count() << "segundos\n\n";

            Matrix all_predictions = Matrix(all_neighbor.rows(), all_neighbor.cols());
            start = chrono::steady_clock::now();
            for (int i = 1; i < all_neighbor.cols() + 1; i++) {
                cout << "Lista la moda " << i << "\n\n";
                Matrix k_neighbor = all_neighbor.block(0, 0, all_neighbor.rows(), i);
                all_predictions.col(i - 1) = vector_moda(k_neighbor);

            }
            end = chrono::steady_clock::now();
            cout << "La matriz de moda tardo " << chrono::duration_cast<chrono::seconds>(end - start).count() << "segundos\n\n";
            matrix2csv(all_predictions, config.path_out, all_predictions_labels(all_predictions.cols(), config.min_k, "vecinos"),
                       arange(1, all_predictions.rows()+1));


            cout << "Calcular y clasificar ks ["<<config.min_k<<","<<config.max_k<<"] para "<<data._train_data.rows()<<" imagenes de train y ";
            cout <<data._test_data.rows()<<" imagenes de test tardo " << chrono::duration<double>(end - start).count() << " segundos\n\n";

            break;
        }
        case PRED_ALFAS:{
            cout<<"\n\nEmpezamos calcular y clasificar rango de alfas PCA\n\n";

            start = chrono::steady_clock::now();
            //Levantamos la data
            Data data = Data(config.path_train, true, config.n_imagenes, config.train_percentage);
            //Iniciamos PCA con el alfa maximo
            PCA pca = PCA(config.max_alfa);
            //Fiteamos PCA con la data de entrada
            if(!config.path_pca_in.empty()){
                cout<<"\n\nLevantamos un csv ya existente\n\n";
                pca.read_binary(config.path_pca_in);
            }else{
                cout<<"\n\nTenemos que conseguir pca de cero\n\n";
                pca.fit(data._train_data);
                if(!config.path_out2.empty()){
                    pca.write_binary(config.path_out2);
                }
            }

            Matrix all_predictions = Matrix(data._test_data.rows(), config.max_alfa-config.min_alfa+1);
            Vector pred = Vector(data._test_data.rows());
            auto start_ciclo = chrono::steady_clock::now();
            auto end_ciclo = chrono::steady_clock::now();
            for(int current_alfa=config.min_alfa; current_alfa <= config.max_alfa; current_alfa++){

                start_ciclo = chrono::steady_clock::now();

                Matrix pca_train = pca.custom_transform(data._train_data, current_alfa);
                Matrix pca_test  = pca.custom_transform(data._test_data, current_alfa);

                clf.fit(pca_train, data._train_labels);
                all_predictions.col(current_alfa-config.min_alfa) = clf.predict(pca_test);

                end_ciclo = chrono::steady_clock::now();

                cout<<"Calculadas las preds de alfa: "<<current_alfa<<". Voy hasta alfa: "<<config.max_alfa;
                cout<<"\nTarde "<<chrono::duration<double>(end_ciclo-start_ciclo).count()<<" segundos\n\n";
            }

            end = chrono::steady_clock::now();
            matrix2csv(all_predictions, config.path_out, all_predictions_labels(all_predictions.cols(), config.min_alfa, "alfa"),
                       arange(1, all_predictions.rows()+1));
            cout << "\n\nCalcular y clasificar alfas ["<<config.min_alfa<<","<<config.max_alfa<<"] para "<<data._train_data.rows()<<" imagenes de train y \n";
            cout <<data._test_data.rows()<<" imagenes de test tardo " << chrono::duration<double>(end - start).count() << " segundos\n\n";
            break;
        }
        default:
            cout<<"\n\nPasaste un modo invalido\n\n";
            assert(false);
    }













//    KNNClassifier cls = KNNClassifier(1);
//    cls.fit(data._data, data._labels);



//    PCA reduced_data = PCA(4);
//    reduced_data.fit(data._data);
////    MatrixXd post_PCA=reduced_data.transform(data._data);
//    cout<<"Porcentaje de varianza: \n"<<reduced_data.var_perc(3)<<endl;
////    Matrix mat(4,3);
//    Vector vect(1);
//    vect << 5;
//    Vector lab(1);
//    lab << 3;
//
//    MatrixXd D(5,5);
//    D<< 5,0,0,0,0,
//        0,4,0,0,0,
//        0,0,3,0,0,
//        0,0,0,2,0,
//        0,0,0,0,1;
//
//    MatrixXd v (5,5);
//    v<< 1,1,1,1,1,
//            1,1,1,1,1,
//            1,1,1,1,1,
//            1,1,1,1,1,
//            1,1,1,1,1;
//    KNNClassifier knn= KNNClassifier(1);
//    knn.mergesort(vect, lab);
//    cout<< vect;


    return 0;
}
