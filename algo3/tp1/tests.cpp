#include "tests.h"
#include <chrono>
#include <fstream>
#include <stdlib.h>
#include <string.h>
#include <algorithm>
#include <random>


int PDNFijo(string csvName, int iteraciones, int N){
    srand(42);
    
    ofstream csv_out(csvName, ofstream::out);
    if(!csv_out.is_open()){
        printf("Error creando el csv %s", csvName.c_str());
        return 1;
    }
    csv_out << "DP_usec,DP_msec,N,R,RES\n";


    for(int paso = 10; paso<=iteraciones; paso++){
        
        //Generamos los vectores de pesos y resistencias al azar
        vector<int> pesos = {};
        vector<int> resistencias = {};
        for(int i = 0; i < N; i++){
            int r = rand() % 3 + 4;
            int w = rand() % 2 + 2;
            pesos.push_back(w);
            resistencias.push_back(r);
        }
        

        uint64_t promedioPDmicro = 0;
        uint64_t promedioPDmili = 0;
        uint64_t resPD;
        for(int subPaso = 0; subPaso < 10; subPaso++){
            //Promediamos el tiempo con la misma instancia para evitar outliers
            auto start = chrono::steady_clock::now();
            resPD = maximaCantidadPD(pesos, resistencias, paso);
            auto end = chrono::steady_clock::now();
            promedioPDmicro += chrono::duration_cast<chrono::microseconds>(end - start).count();
            promedioPDmili += chrono::duration_cast<chrono::milliseconds>(end - start).count();
        }
        
        promedioPDmicro /= 10;
        promedioPDmili /= 10;
        
        //Tiramos toda la data al csv
        csv_out << promedioPDmicro<<",";
        csv_out << promedioPDmili<<",";
        csv_out << N<<",";
        csv_out << paso<<",";
        csv_out << resPD<<endl;

        cout<<paso<<endl;
    }
    csv_out.close();
    return 0;
}

int PDRFijo(string csvName, int iteraciones, int R){
    srand(42);
    
    ofstream csv_out(csvName, ofstream::out);
    if(!csv_out.is_open()){
        printf("Error creando el csv %s", csvName.c_str());
        return 1;
    }
    csv_out << "DP_usec,DP_msec,N,R,RES\n";


    for(int paso = 1; paso<=iteraciones; paso++){
        
        //Generamos los vectores de pesos y resistencias al azar
        vector<int> pesos = {};
        vector<int> resistencias = {};
        for(int i = 0; i < paso; i++){
            int r = rand() % 3 + 4;
            int w = rand() % 2 + 2;
            pesos.push_back(w);
            resistencias.push_back(r);
        }
        

        uint64_t promedioPDmicro = 0;
        uint64_t promedioPDmili = 0;
        uint64_t resPD;
        for(int subPaso = 0; subPaso < 10; subPaso++){
            //Promediamos el tiempo con la misma instancia para evitar outliers
            auto start = chrono::steady_clock::now();
            resPD = maximaCantidadPD(pesos, resistencias, R);
            auto end = chrono::steady_clock::now();
            promedioPDmicro += chrono::duration_cast<chrono::microseconds>(end - start).count();
            promedioPDmili += chrono::duration_cast<chrono::milliseconds>(end - start).count();
        }
        
        promedioPDmicro /= 10;
        promedioPDmili /= 10;
        
        //Tiramos toda la data al csv
        csv_out << promedioPDmicro<<",";
        csv_out << promedioPDmili<<",";
        csv_out << paso<<",";
        csv_out << R<<",";
        csv_out << resPD<<endl;

        cout<<paso<<endl;
    }
    csv_out.close();
    return 0;
}

int PDVariandoTodo(string csvName, vector<int> &Ns, vector<int> &Rs){
    srand(42);
    
    ofstream csv_out(csvName, ofstream::out);
    if(!csv_out.is_open()){
        printf("Error creando el csv %s", csvName.c_str());
        return 1;
    }
    csv_out << "DP_usec,DP_msec,N,R,RES\n";
    int totalIts = Ns.size() * Rs.size();

    //Iteramos para cada combinacion posible (N,R)
    for(int n : Ns){
        for(int r : Rs){
            //Generamos los vectores de pesos y resistencias al azar
            vector<int> pesos = {};
            vector<int> resistencias = {};
            for(int i = 0; i < n; i++){
                int r = rand() % 45 + 5;
                int w = rand() % 6 + 4;
                pesos.push_back(w);
                resistencias.push_back(r);
            }

        uint64_t promedioPDmicro = 0;
        uint64_t promedioPDmili = 0;
        uint64_t resPD;
        for(int subPaso = 0; subPaso < 10; subPaso++){
            //Promediamos el tiempo con la misma instancia para evitar outliers
            auto start = chrono::steady_clock::now();
            resPD = maximaCantidadPD(pesos, resistencias, r);
            auto end = chrono::steady_clock::now();
            promedioPDmicro += chrono::duration_cast<chrono::microseconds>(end - start).count();
            promedioPDmili += chrono::duration_cast<chrono::milliseconds>(end - start).count();
        }
        
        promedioPDmicro /= 10;
        promedioPDmili /= 10;
        
        //Tiramos toda la data al csv
        csv_out << promedioPDmicro<<",";
        csv_out << promedioPDmili<<",";
        csv_out << n<<",";
        csv_out << r<<",";
        csv_out << resPD<<endl;

        cout<<totalIts--<<endl;
            
        }
    }
    csv_out.close();
    return 0;
}

int FBVariandoN(string csvName, int low, int high, int R){
    srand(42);
    
    ofstream csv_out(csvName, ofstream::out);
    if(!csv_out.is_open()){
        printf("Error creando el csv %s", csvName.c_str());
        return 1;
    }
    csv_out << "N,FB_usec,FB_msec,R,RES\n";

    for(int paso = low; paso<=high; paso++){
        
        //Generamos los vectores de pesos y resistencias al azar
        vector<int> pesos = {};
        vector<int> resistencias = {};
        for(int i = 1; i <= paso; i++){
            int r = rand() % 45 + 5;
            int w = rand() % 6 + 4;
            pesos.push_back(w);
            resistencias.push_back(r);
        }

        uint64_t promedioFBmicro = 0;
        uint64_t promedioFBmili = 0;
        int resFB;
        for(int subPaso = 0; subPaso < 10; subPaso++){
            
            //Promediamos el tiempo con la misma instancia para evitar outliers
            auto start = chrono::steady_clock::now();
            resFB = maximaCantidadFB(pesos, resistencias, R);
            auto end = chrono::steady_clock::now();
            promedioFBmicro += chrono::duration_cast<chrono::microseconds>(end - start).count();
            promedioFBmili += chrono::duration_cast<chrono::milliseconds>(end - start).count();

        }
        promedioFBmicro /= 10;
        promedioFBmili /= 10;
        
        //Tiramos toda la data al csv
        csv_out << paso<<",";
        csv_out << promedioFBmicro<<",";
        csv_out << promedioFBmili<<",";
        csv_out << R<<",";
        csv_out << resFB<<endl;

        cout<<paso<<endl;
    }
    csv_out.close();
    return 0;
}


int BTVariandoN(string csvName, int low, int high, int R, bool poda1, bool poda2){
    srand(42);
    
    ofstream csv_out(csvName, ofstream::out);
    if(!csv_out.is_open()){
        printf("Error creando el csv %s", csvName.c_str());
        return 1;
    }
    csv_out << "N,BTusec,BTmsec,R,RES\n";
    auto rng = default_random_engine {};
    for(int paso = low; paso<=high; paso++){
        
        vector<int> pesos = {};
        vector<int> resistencias = {};
        //Generamos los vectores de pesos y resistencias al azar
        for(int i = 1; i <= paso; i++){
            //Equal
            int w = rand() % 30 + 30;
            int r = rand() % 30 + 30;
            
            //Bigger
            //int r = rand() % 30 + 75;
            //int w = rand() % 30 + 30;
            
            //Smaller
            //int r = rand() % 30 + 30;
            //int w = rand() % 30 + 75;

            //Mitad de los objetos
            //int r, w;
        //     if(i<=paso*(9.5/10)){
        //         w = 1;
        //         r = 2*R;
        //     }else{
        //         w = 2*R;
        //         r = 1;
        //    }
            pesos.push_back(w);
            resistencias.push_back(r);
        }

        uint64_t promedioBTmicro = 0;
        uint64_t promedioBTmili = 0;
        int resBT;
        for(int subPaso = 0; subPaso < 10; subPaso++){

            //Generamos los vectores de pesos y resistencias al azar
            auto start = chrono::steady_clock::now();
            resBT = maximaCantidadBT(pesos, resistencias, R, poda1, poda2);
            auto end = chrono::steady_clock::now();
            promedioBTmicro += chrono::duration_cast<chrono::microseconds>(end - start).count();
            promedioBTmili += chrono::duration_cast<chrono::milliseconds>(end - start).count();

        }

        promedioBTmicro /= 10;
        promedioBTmili /= 10;

        //Tiramos toda la data al csv
        csv_out << paso<<",";
        csv_out << promedioBTmicro<<",";
        csv_out << promedioBTmili<<",";
        csv_out << R <<",";
        csv_out << resBT <<endl;

        cout<<paso<<endl;
    }
    csv_out.close();
    return 0;
}


int resolverTests(){
    auto start = chrono::steady_clock::now();
    int res = 0;

    if(PDRFijo("data/PDRFijo.csv", 10000, 1000)){
        res = 1;
        printf("Fallo mejor caso PD");
    }
    if(PDNFijo("data/PDNFijo.csv", 10000, 100)){
        res = 1;
        printf("Fallo mejor caso PD");
    }
    
    //Ns y Rs para el heatmap
    vector<int> Rs;
    vector<int> Ns;
    for(int i = 1000; i < 8000; i+=500){
        Rs.push_back(i);
        Ns.push_back(i);
    }
    if(PDVariandoTodo("data/PDVariandoTodo.csv", Ns, Rs)){
        res = 1;
        printf("Fallo PD cross val");
    }
    if(FBVariandoN("data/FBVariandoN.csv", 0, 30, 20)){
        res = 1;
        printf("Fallo FB variando N\n");
    }
    if(BTVariandoN("data/BTAmbasPodas.csv", 0, 50, 1000, true, true)){
        res = 1;
        printf("Fallo BT ambas podas");
    }
    if(BTVariandoN("data/BTFact.csv", 0, 50, 1000, true, false)){
        res = 1;
        printf("Fallo BT factibilidad");
    }
    if(BTVariandoN("data/BTOpt.csv", 0, 50, 1000, false, true)){
        res = 1;
        printf("Fallo BT optimalidad");
    }

    auto end = chrono::steady_clock::now();
    int duracion = chrono::duration_cast<chrono::minutes>(end - start).count();

    printf("El programa tardo %d minutos", duracion);

    

    return res;

}
