//
// Created by juampi on 24/10/20.
//

#ifndef TP2_TOMAR_PARAMETROS_H
#define TP2_TOMAR_PARAMETROS_H

#include "types.h"
#include "getopt.h"
#include "unistd.h"

#define KNN             0
#define PCA_KNN         1
#define PRED_VECINOS    2
#define PRED_ALFAS      3

using namespace std;

void procesar_opciones(int argc, char **argv, config_t *config);
void chequear_parametros(config_t *config);

#endif //TP2_TOMAR_PARAMETROS_H
