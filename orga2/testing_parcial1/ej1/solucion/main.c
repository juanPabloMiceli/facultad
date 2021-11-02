#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <assert.h>
#include <math.h>
#include <unistd.h>

#include "lib.h"


void test_tree(FILE *pfile){
    tree_t* arbolito = treeNew(TypeInt, TypeString, 1);
    tree_t* arbolito_inverso = treeNew(TypeInt, TypeString, 1);

    int key1 = 24;
    int key2 = 34;
    int key3 = 24;
    int key4 = 11;
    int key5 = 31;
    int key6 = 11;
    int key7 = -2;
    char * data1 = "papanatas";
    char * data2 = "rima";
    char * data3 = "buscabullas";
    char * data4 = "musica";
    char * data5 = "Pikachu";
    char * data6 = "Bulbasaur";
    char * data7 = "Charmander";


    assert(treeInsert(arbolito, &key1, data1) == 1);
    assert(treeInsert(arbolito, &key2, data2) == 1);
    assert(treeInsert(arbolito, &key3, data3) == 1);
    assert(treeInsert(arbolito, &key4, data4) == 1);
    assert(treeInsert(arbolito, &key5, data5) == 1);
    assert(treeInsert(arbolito, &key6, data6) == 1);
    assert(treeInsert(arbolito, &key7, data7) == 1);


    assert(treeInsert(arbolito_inverso, &key7, data7) == 1);
    assert(treeInsert(arbolito_inverso, &key6, data6) == 1);
    assert(treeInsert(arbolito_inverso, &key5, data5) == 1);
    assert(treeInsert(arbolito_inverso, &key4, data4) == 1);
    assert(treeInsert(arbolito_inverso, &key3, data3) == 1);
    assert(treeInsert(arbolito_inverso, &key2, data2) == 1);
    assert(treeInsert(arbolito_inverso, &key1, data1) == 1);


    treePrint(arbolito, pfile);
    treePrint(arbolito_inverso, pfile);

    treeDelete(arbolito);
    treeDelete(arbolito_inverso);
}

void test_document(FILE *pfile){
	int32_t size = 6;
	int n1 = 32;
	int n2 = 10;
	float x1 = 123.432;
	float x2 = 42.0303030; 
	char* texto1 = "Hola"; 
	char* texto2 = "Chau";
    
    document_t *doc = docNew(size, TypeFloat, &x1, TypeString, texto1, TypeInt, &n1, TypeInt, &n2, TypeFloat, &x2, TypeString, texto2);
    document_t *clone = docClone(doc);

    docPrint(doc,pfile);
    docPrint(clone,pfile);

    docDelete(doc);
    docDelete(clone);

}


void test_list(FILE *pfile){
    char *s1 = strClone("Dario");
    char *s2 = strClone("David");
    char *s3 = strClone("Furfi");
    char *s4 = strClone("Guada");
    char *s5 = strClone("Joaquin");
    char *s6 = strClone("Juampi");
    char *s7 = strClone("Macarena");
    char *s8 = strClone("Marco");
    char *s9 = strClone("Tomas");
    char *s10 = strClone("Vicky");


	list_t *l_string = listNew(TypeString);
	
	listAdd(l_string, s7);
	listAdd(l_string, s10);
	listAdd(l_string, s5);
	listAdd(l_string, s6);
	listAdd(l_string, s2);
	listAdd(l_string, s9);
	listAdd(l_string, s4);
	listAdd(l_string, s1);
	listAdd(l_string, s3);
	listAdd(l_string, s8);

	float pi_ = 3.14;
	float e_ = 2.71;
	float raiz_de_2_ = 1.414213562;
	float aureo_ = 1.61;
	float la_nota_de_juampi_y_vicky_en_el_final_de_orga_2_ = 10.0;

	float *pi = floatClone(&pi_);
	float *e = floatClone(&e_);
	float *raiz_de_2 = floatClone(&raiz_de_2_);
	float *aureo = floatClone(&aureo_);
	float *la_nota_de_juampi_y_vicky_en_el_final_de_orga_2 = floatClone(&la_nota_de_juampi_y_vicky_en_el_final_de_orga_2_);


	list_t *l_float = listNew(TypeFloat);

	listAdd(l_float, pi);
	listAdd(l_float, e);
	listAdd(l_float, raiz_de_2);
	listAdd(l_float, aureo);
	listAdd(l_float, la_nota_de_juampi_y_vicky_en_el_final_de_orga_2);

	list_t *l_string_clone = listClone(l_string);
	list_t *l_float_clone = listClone(l_float);

	listPrint(l_float, pfile);
	listPrint(l_string, pfile);

	listDelete(l_string);
	listDelete(l_string_clone);
	listDelete(l_float);
	listDelete(l_float_clone);

}

int main (void){

    FILE *pfile = fopen("salida.caso.propios.txt","w");
    test_document(pfile);
    test_list(pfile);
    test_tree(pfile);
    
    fclose(pfile);
    
    return 0;
}
