//
// Created by juampi on 24/10/20.
//

#include "fstream"
#include "tomar_parametros.h"
#include "iostream"

using namespace std;

void procesar_opciones(int argc, char **argv, config_t *config){


    //Valores por defecto
    config->metodo      = -1;
    config->path_train  = "";
    config->path_pca_in = "";
    config->path_test   = "";
    config->path_out    = "";
    config->path_out2   = "";

    config->n_imagenes  = -1;
    config->min_k       =  1;
    config->max_k       = 20;
    config->min_alfa    =  1;
    config->max_alfa    = 50;

    config->train_percentage = 0.8;
    config->k_neighbors      =   3;
    config->pca_alfa         =  19;

    const char* const op_cortas = "m:i:q:o:n:p:k:A:P:";

    const struct option op_largas[] = {
            { "metodo",         1, NULL, 'm' },
            { "training",       1, NULL, 'i' },
            { "testing",        1, NULL, 'q' },
            { "out",            1, NULL, 'o' },
            { "n_imagenes",     1, NULL, 'n' },
            { "min_k",          1, NULL, '1' },
            { "max_k",          1, NULL, '2' },
            { "min_alfa",       1, NULL, '3' },
            { "max_alfa",       1, NULL, '4' },
            { "train_p",        1, NULL, 'p' },
            { "k_neighbors",    1, NULL, 'k' },
            { "PCA_alfa",       1, NULL, 'A' },
            { "levantar_pca",   1, NULL, 'P' },
            { NULL,             0, NULL,  0  }
    };
    int siguiente_opcion;
    while (1) {
        siguiente_opcion = getopt_long ( argc, argv, op_cortas, op_largas, NULL);

        // No hay mas opciones
        if ( siguiente_opcion == -1 )
            break;

        // Procesar opcion
        switch ( siguiente_opcion ) {
            case 'm' :
                config->metodo = atoi (optarg);
                break;
            case 'i' :
                config->path_train =  optarg ;
                break;
            case 'q' :
                config->path_test = optarg;
                break;
            case 'o' :
                if(config->path_out.empty()){
                    config->path_out = optarg;
                }else if(config->path_out2.empty()){
                    config->path_out2 = optarg;
                }
                break;
            case 'n' :
                config->n_imagenes = atoi(optarg);
                break;
            case '1' :
                 config->min_k = atoi(optarg);
                break;
            case '2' :
                config->max_k = atoi (optarg);
                break;
            case '3' :
                config->min_alfa = atoi(optarg);
                break;
            case '4' :
                config->max_alfa = atoi (optarg);
                break;
            case 'p' :
                config->train_percentage = atof(optarg);
                break;
            case 'k' :
                config->k_neighbors = atoi (optarg);
                break;
            case 'A' :
                config->pca_alfa = atoi(optarg);
                break;
            case 'P' :
                config->path_pca_in = optarg;
                break;
            default : /* opcion no valida */
                abort ( );
        }
    }
}

void chequear_parametros(config_t *config){

    //Chequear que se pasaron todos los csvs necesarios
    if(config->path_train.empty()){
        cout<<"\n\nNo pasaste el archivo de train\n\n";
        assert(false);
    }

    if(config->path_out.empty()){
        cout<<"\n\nNo pasaste el archivo de salida\n\n";
        assert(false);
    }

    if((config->metodo == KNN || config->metodo == PCA_KNN) && config->path_test.empty()){
        cout<<"\n\nNo pasaste el archivo de test\n\n";
        assert(false);
    }


    //Chequear que existan los archivos de entrada

    if(!config->path_train.empty()){
        std::ifstream csv_train(config->path_train);
        if (!csv_train.good()) {
            cout << "\n\nEl archivo de train no existe\n\n";
            assert(false);
        }
        csv_train.close();
    }

    if(!config->path_test.empty()){
        std::ifstream csv_test(config->path_test);
        if(!csv_test.good()){
            cout<<"\n\nEl archivo de test no existe\n\n";
            assert(false);
        }
        csv_test.close();
    }

    if(!config->path_pca_in.empty()){
        std::ifstream csv_pca(config->path_pca_in);
        if (!csv_pca.good()) {
            cout << "\n\nEl archivo de los autovectores de pca no existe\n\n";
            assert(false);
        }
        csv_pca.close();
    }

    //Parametros internos
    if(config->train_percentage > 1 || config->train_percentage < 0){
        cout<<"\n\nTratemos de que train_percentage (-p) este entre 0 y 1\n\n";
        assert(false);
    }
}