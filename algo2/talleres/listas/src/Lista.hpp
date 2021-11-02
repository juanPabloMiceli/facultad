/**
* Datos:
* Nombre y apellido: Juan Pablo Miceli
* LU: 424/19
* mail: micelijuanpablo@gmail.com
*
*/

#include "Lista.h"

Lista::Lista() : _length(0), _head(nullptr), _last(nullptr) {}

Lista::Lista(const Lista& l) : Lista() {
    //Inicializa una lista vacía y luego utiliza operator= para no duplicar el código de la copia de una lista.
    *this = l;
}

void Lista::destruir() {
    Node* node = _head;
    while (_head != nullptr) {
        node = node->next_node;
        delete (_head);
        _head = node;
    }
    _length = 0;
}

Lista::~Lista() {
    destruir();
}

Lista& Lista::operator=(const Lista& aCopiar) {
    //Primero limpio la lista original por si tenía basura
    destruir();
    for (int i = 0; i < aCopiar.longitud(); i++) {
        this->agregarAtras(aCopiar.iesimo(i));
    }
    return *this;
}

void Lista::agregarAdelante(const int& elem) {
    Node* node = new Node(elem);

    if (_head == nullptr) {
        _head = node;
        _last = node;
        _length++;
        return;
    }

    _head->prev_node = node;
    node->next_node = _head;

    _head = node;
    _length++;
}

void Lista::agregarAtras(const int& elem) {
    Node* node = new Node(elem);
    if (_head == nullptr) {
        _head = node;
        _last = node;
        _length++;
        return;
    }

    _last->next_node = node;
    node->prev_node = _last;

    _last = node;
    _length++;
}

void Lista::eliminar(Nat i) {
    Node* temp = _head;
    Node* prev;
    Node* next;

    while (i > 0) {
        temp = temp->next_node;
        i--;
    }

    next = temp->next_node;
    prev = temp->prev_node;

    if (next == nullptr && prev == nullptr) {
        _head = nullptr;
        _last = nullptr;

    } else if (next == nullptr) {
        _last = prev;
        prev->next_node = nullptr;

    } else if (prev == nullptr) {
        _head = next;
        next->prev_node = nullptr;

    } else {
        prev->next_node = next;
        next->prev_node = prev;
    }

    _length--;
    delete temp;
}

int Lista::longitud() const {
    return _length;
}

const int& Lista::iesimo(Nat i) const {
    assert(i < _length);

    Node* res = _head;
    while (i > 0) {
        res = res->next_node;
        i--;
    }

    return res->value;
}

int& Lista::iesimo(Nat i) {
    assert(i < _length);

    Node* res = _head;
    while (i > 0) {
        res = res->next_node;
        i--;
    }

    return res->value;
}

void Lista::mostrar(ostream& o) {
    if (_head == nullptr) {
        o << "[]";
        return;
    }

    Node* node = _head;
    o << "[";
    for (int i = 0; i < _length - 1; i++) {
        o << node->value << ", ";
        node = node->next_node;
    }
    o << node->value << "]";
}

Lista::Node::Node(const int& elem) : value(elem), next_node(nullptr), prev_node(nullptr) {}
