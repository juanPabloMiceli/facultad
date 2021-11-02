#include "lib.h"


int resolverTests();
int PDNFijo(string csvName, int iteraciones, int N);
int PDRFijo(string csvName, int iteraciones, int R);
int PDVariandoTodo(string csvName, vector<int> &Ns, vector<int> &Rs);
int FBVariandoN(string csvName, int low, int high, int R);
int BTVariandoN(string csvName, int low, int high, int R, bool poda1, bool poda2);