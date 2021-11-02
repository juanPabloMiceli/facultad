#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <ctype.h>
#include <string.h>
#include <assert.h>
#include <math.h>
#include <stdbool.h>
#include <unistd.h>
#include <stdarg.h>

typedef enum e_type {
    TypeNone = 0,
    TypeInt = 1,
    TypeFloat = 2,
    TypeString = 3,
    TypeDocument = 4
} type_t;

typedef int32_t (funcCmp_t)(void*, void*);
typedef void* (funcClone_t)(void*);
typedef void (funcDelete_t)(void*);
typedef void (funcPrint_t)(void*, FILE *pFile);

/** Int **/

int32_t intCmp(int32_t* a, int32_t* b);
int32_t* intClone(int32_t* a);
void intDelete(int32_t* a);
void intPrint(int32_t* a, FILE *pFile);

/** Float **/

int32_t floatCmp(float* a, float* b);
float* floatClone(float* a);
void floatDelete(float* a);
void floatPrint(float* a, FILE *pFile);

/* String */

uint32_t strLen(char* a);
int32_t strCmp(char* a, char* b);
char* strClone(char* a);
void strDelete(char* a);
void strPrint(char* a, FILE *pFile);

/** Document **/

typedef struct s_document {
    int count;					//En 0		//4bytes
    struct s_docElem *values;	//En 8		//8bytes
} document_t;								//Ocupa 16bytes

typedef struct s_docElem {
    type_t type;				//En 0		//4bytes
    void *data;					//En 8		//8bytes
} docElem_t;								//Ocupa 16bytes

document_t* docNew(int32_t size, ... );
int32_t docCmp(document_t* a, document_t* b);
document_t* docClone(document_t* a);
void docDelete(document_t* a);
void docPrint(document_t* a, FILE *pFile);

/* List */

typedef struct s_list {
    type_t   type;              //En 4      //4Bytes
    uint32_t size;              //En 0      //4Bytes
    struct s_listElem *first;   //En 8      //8Bytes
    struct s_listElem *last;    //En 16     //8Bytes
} list_t;                       //Ocupa 24 bytes

typedef struct s_listElem {
    void *data;                 //En 0      //8Bytes
    struct s_listElem *next;    //En 8      //8Bytes
    struct s_listElem *prev;    //En 16     //8Bytes
} listElem_t;                   //Ocupa 24 bytes



list_t* listNew(type_t t);
void listAdd(list_t* l, void* data);
void listRemove(list_t* l, void* data);
list_t* listClone(list_t* l);
void listDelete(list_t* l);
void listPrint(list_t* l, FILE *pFile);



/** tree **/

typedef struct s_tree {
    struct s_treeNode *first;       //En 0      //8Bytes
    uint32_t size;                  //En 8      //4Bytes
    type_t typeKey;                 //En 12     //4Bytes
    int    duplicate;               //En 16     //4Bytes
    type_t typeData;                //En 20     //4Bytes
} tree_t;                           //Ocupa 24 bytes

typedef struct s_treeNode {
    void *key;                      //En 0      //8Bytes
    list_t *values;                 //En 8      //8Bytes
    struct s_treeNode *left;        //En 16     //8Bytes
    struct s_treeNode *right;       //En 24     //8Bytes
} treeNode_t;                       //Ocupa 32 bytes




tree_t* treeNew(type_t typeKey, type_t typeData, int duplicate);
int treeInsert(tree_t* tree, void* key, void* data);
list_t* treeGet(tree_t* tree, void* key);
void treeRemove(tree_t* tree, void* key, void* data);
void treeDelete(tree_t* tree);
void treePrint(tree_t* tree, FILE *pFile);




int docSimilar(document_t* a, document_t* b, void* bitmap);