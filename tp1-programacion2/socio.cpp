#include <iostream>
#include <cstdio>
#include <limits>
#include "Socio.h"
using namespace std;

void Socio::cargar() {
    bool entro = false;
    while (!entro) {
        cout << "ID Socio: ";
        cin >> idSocio;

        if (cin.fail()) {
            cin.clear();  // limpia el estado de error
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // limpia todo el buffer
            cout << "Entrada invalida. Intenta de nuevo.\n";
        } else {
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // limpia todo el buffer
            entro = true;  // válida
            cout << "Se ingreso correctamente.\n";
        }
    }

    cout << "Nombre: ";
    cin.getline(nombre, 20);
    cout << "Apellido: ";
    cin.getline(apellido, 20);
    cout << "Telefono: ";
    cin.getline(telefono, 15);
    eliminado = false;
}

void Socio::mostrar() const {
    if (!eliminado) {
        cout << "ID: " << idSocio
             << " | " << nombre << " " << apellido
             << " | Tel: " << telefono << endl;
    }
}

int Socio::getIdSocio() const { return idSocio; }

bool Socio::getEliminado() const { return eliminado; }

void Socio::setEliminado(bool e) { eliminado = e; }

/// Archivo
bool Socio::guardar() {
    FILE *p = fopen("socios.dat", "ab");
    if (p == NULL) return false;
    fwrite(this, sizeof(Socio), 1, p);
    fclose(p);
    return true;
}

bool Socio::leer(int pos) {
    FILE *p = fopen("socios.dat", "rb");
    if (p == NULL) return false;
    fseek(p, pos * sizeof(Socio), 0);
    bool leyo = fread(this, sizeof(Socio), 1, p);
    fclose(p);
    return leyo;
}

bool Socio::modificar(int pos) {
    FILE *p = fopen("socios.dat", "rb+");
    if (p == NULL) return false;
    fseek(p, pos * sizeof(Socio), 0);
    bool ok = fwrite(this, sizeof(Socio), 1, p);
    fclose(p);
    return ok;
}
