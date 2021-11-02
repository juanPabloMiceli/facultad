#include "SistemaDeMensajes.h"

// Completar...

SistemaDeMensajes::~SistemaDeMensajes() {
    for(int i = 0;i < 4;i++){
        delete _conns[i];
        _conns[i] = nullptr;
    }

    for(int i = _proxys.size() - 1;i >= 0;i--){
        delete _proxys[i];
        _proxys[i] = nullptr;
    }

}

SistemaDeMensajes::SistemaDeMensajes() : _conns(), _proxys() {
};
// Pre: 0 <= id < 4
void SistemaDeMensajes::registrarJugador(int id, string ip){
    if(_conns[id] == nullptr){
        _conns[id] = new ConexionJugador(ip);
    }
    else {
        delete _conns[id];
        _conns[id] = new ConexionJugador(ip);
    }
}
// Pre: 0 <= id < 4
bool SistemaDeMensajes::registrado(int id) const {
    return _conns[id] != nullptr;
}

// Pre: registrado(id)
void SistemaDeMensajes::enviarMensaje(int id, string mensaje){
    _conns[id]->enviarMensaje(mensaje);
}

// Pre: registrado(id)
string SistemaDeMensajes::ipJugador(int id) const {
    return _conns[id]->ip();
}

void SistemaDeMensajes::desregistrarJugador(int id) {

    delete _conns[id];

    _conns[id] = nullptr;

}

SistemaDeMensajes::Proxy * SistemaDeMensajes::obtenerProxy(int id) {
    Proxy* proxy = new Proxy(&_conns[id]);
    _proxys.push_back(proxy);
    return proxy;
}

SistemaDeMensajes::Proxy::Proxy(ConexionJugador** conn) : _conn(conn) {}

void SistemaDeMensajes::Proxy::enviarMensaje(string msg){
    (*_conn)->enviarMensaje(msg);
}
