#include <iostream>

using namespace std;

// Ejercicio 1

class Rectangulo {
    public:
        Rectangulo(unsigned int alto, unsigned int ancho);
        unsigned int alto();
        unsigned int ancho();
        float area();

    private:
        unsigned int alto_;
        unsigned int ancho_;

};

Rectangulo::Rectangulo(unsigned int alto, unsigned int ancho) : alto_(alto), ancho_(ancho) {};



unsigned int Rectangulo::alto() { return alto_; }

// Completar definición: ancho
unsigned int Rectangulo::ancho() { return ancho_; }
// Completar definición: area
float Rectangulo::area() {
    return ancho_ * alto_;
}
// Ejercicio 2


// Clase Elipse

class Elipse{
public:
    Elipse(unsigned int a, unsigned int b);

    unsigned int r_a();
    unsigned int r_b();
    float area();

private:
    unsigned int _a;
    unsigned int _b;
    float _PI = 3.14;
};

Elipse::Elipse(unsigned int a, unsigned int b) : _a(a), _b(b) {};

unsigned int Elipse::r_a() {return _a; }

unsigned int Elipse::r_b() {return _b; }

float Elipse::area(){return _a*_b*_PI; }


// Ejercicio 3

class Cuadrado {
    public:
        Cuadrado(unsigned int lado);
        unsigned int lado();
        float area();

    private:
        Rectangulo r_;
};

Cuadrado::Cuadrado(unsigned int lado): r_(lado, lado) {}

unsigned int Cuadrado::lado() {
    return r_.alto();
}

float Cuadrado::area() {
    return r_.area();
}

// Ejercicio 4

class Circulo{
public:
    Circulo(unsigned int radio);
    unsigned int radio();
    float area();

private:
    Elipse _elipse;
};


Circulo::Circulo(unsigned int radio) : _elipse(radio, radio) {}

unsigned int Circulo::radio() { return _elipse.r_a();}

float Circulo::area(){ return _elipse.area(); }


// Ejercicio 5

ostream& operator<<(ostream& os, Rectangulo r) {
    os << "Rect(" << r.alto() << ", " << r.ancho() << ")";
    return os;
}

// ostream Elipse
ostream& operator<<(ostream& os, Elipse e) {
    os << "Elipse(" << e.r_a() << ", " << e.r_b() << ")";
    return os;
}

// Ejercicio 6

ostream& operator<<(ostream& os, Cuadrado c){
    os << "Cuad(" << c.lado() << ")";
    return os;
}

ostream& operator<<(ostream& os, Circulo c){
    os << "Circ(" << c.radio() << ")";
    return os;
}

