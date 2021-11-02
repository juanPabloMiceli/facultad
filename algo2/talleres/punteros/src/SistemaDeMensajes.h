#ifndef SISTEMADEMENSAJES_H
#define SISTEMADEMENSAJES_H

#include "ConexionJugador.h"
#include <string>
#include "Proxy.h"
#include "vector"
//#include "Proxy2.h"


using namespace std;

class SistemaDeMensajes {
  public:

    class Proxy;

    ~SistemaDeMensajes();
    SistemaDeMensajes();
    // Pre: 0 <= id < 4
    void registrarJugador(int id, string ip);
    // Pre: 0 <= id < 4
    bool registrado(int id) const;

    // Pre: registrado(id)
    void enviarMensaje(int id, string mensaje);

    // Pre: registrado(id)
    string ipJugador(int id) const;

    void desregistrarJugador(int id);

    SistemaDeMensajes::Proxy * obtenerProxy(int id);



    class Proxy{
    public:
        Proxy(ConexionJugador** conn);
        void enviarMensaje(string msg);

    private:
        ConexionJugador** _conn;

        // No puedo copiarlo
        Proxy(const Proxy&);
    };





  private:
    ConexionJugador* _conns[4];
    vector<Proxy*> _proxys;
};

#endif