/*
 * Taller Guia 1, Algo 2
 * Nombre:  MICELI, Juan Pablo
 * LU:      424/19
 * */


#include <iostream>
using namespace std;



// Pre: 0 <= mes < 12
unsigned int dias_en_mes(unsigned int mes) {
    unsigned int dias[] = {
        // ene, feb, mar, abr, may, jun
        31, 28, 31, 30, 31, 30,
        // jul, ago, sep, oct, nov, dic
        31, 31, 30, 31, 30, 31
    };
    return dias[mes - 1];
}

// Ejercicio 7, 8, 9 y 10


class Fecha {
public:
    Fecha(int dia, int mes);

    int mes() const;
    int dia() const;
    bool operator==(const Fecha& f2) const;
    bool operator<(const Fecha& f2) const;
    void incrementar_dia();

private:
    int _dia;
    int _mes;
};

Fecha::Fecha(int mes, int dia) : _dia(dia), _mes(mes) {};

int Fecha::mes() const { return _mes; }

int Fecha::dia() const { return _dia; }


ostream& operator<<(ostream& os, Fecha f){
    os << f.dia() << "/" << f.mes();
    return os;
}

bool Fecha::operator==(const Fecha  &f2) const {
    return _dia == f2.dia() && _mes == f2.mes();
}

bool Fecha::operator<(const Fecha &f2) const{
    return (_mes < f2.mes()) || (_mes == f2.mes() && _dia < f2.dia());
}


void Fecha::incrementar_dia() {
    if(_dia == dias_en_mes(_mes)){
        _mes++;
        _dia = 1;
    }
    else{
        _dia++;
    }
}


// Ejercicio 11, 12

// Clase Horario
class Horario{
public:
    Horario(unsigned int hora, unsigned int min);
    unsigned int hora();
    unsigned int min();
    bool operator<(Horario h2);

private:
    int _hora;
    int _min;
};

Horario::Horario(unsigned int hora, unsigned int min) : _hora(hora), _min(min) {};

unsigned int Horario::hora() { return _hora; }

unsigned int Horario::min() { return _min; }

ostream& operator<<(ostream& os, Horario h){
    os << h.hora() <<":" << h.min();
    return os;
}

bool Horario::operator<(Horario h2) {
    return (_hora < h2.hora()) || (_hora == h2.hora() && _min < h2.min());
}



// Ejercicio 13

class Recordatorio{
public:
    Recordatorio(Fecha fecha, Horario horario, string mensaje);
    Fecha fecha();
    Horario horario();
    string mensaje();

private:
    Fecha _fecha;
    Horario _horario;
    string _mensaje;
};


Recordatorio::Recordatorio(Fecha fecha, Horario horario, string mensaje) : _fecha(fecha), _horario(horario), _mensaje(mensaje) {}

Fecha Recordatorio::fecha() { return _fecha; }

Horario Recordatorio::horario() { return _horario; }

string Recordatorio::mensaje() { return _mensaje; }

ostream& operator<<(ostream& os, Recordatorio r){
    os << r.mensaje() << " @ " << r.fecha() << " " << r.horario();
    return os;
}



// Ejercicio 14

class Agenda{
public:
    void agregar_recordatorio(Recordatorio rec);
    void incrementar_dia();
    vector<Recordatorio> recordatorios_de_hoy();
    Fecha hoy();


    Agenda(Fecha fecha_inicial);

private:
    Fecha _fecha_actual;
    map<Fecha, vector<Recordatorio>> _recordatorios;
};

Agenda::Agenda(Fecha fecha_inicial) : _fecha_actual(fecha_inicial), _recordatorios(){}


void Agenda::incrementar_dia() {
    _fecha_actual.incrementar_dia();
}

Fecha Agenda::hoy() { return _fecha_actual; }


vector<Recordatorio> Agenda::recordatorios_de_hoy() {
    vector<Recordatorio> res;
    if(_recordatorios.count(_fecha_actual)){
        res = _recordatorios.at(_fecha_actual);
    }
    return res;
}


vector<Recordatorio> sort_recordatorios(vector<Recordatorio> v){
    int i = v.size()-1;
    while(i > 0 && (v[i].horario() < v[i-1].horario())){
        swap(v[i], v[i-1]);
        i--;
    }

    return v;
}

void Agenda::agregar_recordatorio(Recordatorio rec){
    Fecha fecha = rec.fecha();

    _recordatorios[fecha].push_back(rec);
    _recordatorios[fecha] = sort_recordatorios(_recordatorios[fecha]);
}

ostream& operator<<(ostream& os, Agenda a){
    os << a.hoy() << endl;
    os << "=====" << endl;
    Fecha hoy = a.hoy();
    vector<Recordatorio> r_de_hoy = a.recordatorios_de_hoy();
    for(int i = 0; i < a.recordatorios_de_hoy().size(); i++){
        os << a.recordatorios_de_hoy()[i] << endl;
    }
    return os;
}


