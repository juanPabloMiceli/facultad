#include <utility>

using namespace std;




// Ejercicio 15

// Juego

using Pos = pair<int, int>;

const char ARRIBA = '^';
const char ABAJO = 'v';
const char DERECHA = '<';
const char IZQUIERDA = '>';


class Pocion{
public:
    Pocion(unsigned int efecto, unsigned int duracion_restante);

    unsigned int efecto() const;
    unsigned int duracion_restante() const;
    void decrementar_duracion();
    bool vacia();
    bool operator<(const Pocion &p) const;


private:
    unsigned int _efecto;
    unsigned int _duracion_restante;
};

Pocion::Pocion(unsigned int efecto, unsigned int duracion_restante) : _efecto(efecto), _duracion_restante(duracion_restante) {}

unsigned int Pocion::efecto() const{ return _efecto; }

unsigned int Pocion::duracion_restante() const{return _duracion_restante; }

void Pocion::decrementar_duracion() {_duracion_restante--;}

bool Pocion::vacia() { return _duracion_restante == 0; }

bool Pocion::operator<(const Pocion &p) const {
    return duracion_restante() < p.duracion_restante();
}

int operator++(const vector<Pocion>& v){//Realiza la sumatoria de efectos de las pociones, devuelve la cantidad de movimientos final, siempre se hace minimo un movimiento
    int res = 0;
    for(Pocion pocion : v){
        res += pocion.efecto();
    }
    return max(1, res);
}

void operator--(vector<Pocion>& v){//decremento la duracion de todas las pociones en 1

    for(Pocion &pocion : v){
        pocion.decrementar_duracion();
    }
}



class Juego {
public:
    Juego(unsigned int casilleros, Pos posicion_inicial);

    Pos posicion_jugador();
    unsigned int turno_actual();
    void mover_jugador(char dir);
    void ingerir_pocion(unsigned int movimientos, unsigned turnos);

private:
    unsigned int _tamanio_tablero;
    unsigned int _movimientos_restantes;
    unsigned int _turno_actual;
    Pos _posicion_actual;
    vector<Pocion> _pociones;

    unsigned int calcular_velocidad();
    void ordenar_pociones(vector<Pocion> &v);
    void limpiar_pociones_vacias(vector<Pocion> &v);
};


Juego::Juego(unsigned int casilleros, Pos posicion_inicial) : _tamanio_tablero(casilleros), _movimientos_restantes(1), _turno_actual(0), _posicion_actual(posicion_inicial), _pociones() {}

Pos Juego::posicion_jugador(){ return _posicion_actual; }

unsigned int Juego::turno_actual(){ return _turno_actual; }

void Juego::mover_jugador(char dir) {

    int min_border = 0;
    int max_border = _tamanio_tablero-1;

    bool movimiento_valido = false;

    switch(dir){
        case IZQUIERDA:
            if(_posicion_actual.second > min_border){
                _posicion_actual.second--;
                movimiento_valido = true;
            }
            break;
        case ABAJO:
            if(_posicion_actual.first < max_border){
                _posicion_actual.first++;
                movimiento_valido = true;
            }
            break;
        case DERECHA:
            if(_posicion_actual.second < max_border){
                _posicion_actual.second++;
                movimiento_valido = true;
            }
            break;
        case ARRIBA:
            if(_posicion_actual.first > min_border){
                _posicion_actual.first--;
                movimiento_valido = true;
            }
            break;
    }



    if(movimiento_valido){
        _movimientos_restantes--;
        if(_movimientos_restantes <= 0){
            --_pociones; //decremento la duracion de todas las pociones en 1
            limpiar_pociones_vacias(_pociones);
            _turno_actual++;
            _movimientos_restantes = ++_pociones;
        }

    }
}

unsigned int Juego::calcular_velocidad() {
    return ++_pociones;
}

void Juego::ordenar_pociones(vector<Pocion> &v){
    int i = v.size()-1;
    while(i > 0 && (v[i-1] < v[i])){
        swap(v[i], v[i-1]);
        i--;
    }
}

void Juego::ingerir_pocion(unsigned int movimientos, unsigned turnos) {
    _pociones.push_back(Pocion(movimientos, turnos));
    ordenar_pociones(_pociones);//Ordeno de manera que al final siempre tenga a las pociones con menos movimientos restantes
    _movimientos_restantes = ++_pociones;

}

void Juego::limpiar_pociones_vacias(vector<Pocion> &v) {
    int last = v.size() - 1;

    while(last >= 0 && v[last].vacia()){
        v.pop_back();
        last--;
    }
}

