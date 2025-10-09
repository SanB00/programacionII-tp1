#include <iostream>
#include <cstdio>
#include <limits>
#include "Prestamo.h"
using namespace std;

void Prestamo::cargar() {

    bool entro = false;
    while (!entro) {
        cout << "ID Prestamo: ";
        cin >> idPrestamo;

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
    cout << "ID Socio: "; cin >> idSocio;
    cout << "ID Libro: "; cin >> idLibro;
    cout << "Fecha Prestamo: \n"; fechaPrestamo.cargar();
    cout << "Fecha Devolucion: \n"; fechaDevolucion.cargar();
}

void Prestamo::mostrar() const {
    cout << "Prestamo ID: " << idPrestamo
         << " | Socio: " << idSocio
         << " | Libro: " << idLibro
         << " | Prestado: "; fechaPrestamo.mostrar();
    cout << " | Devuelto: "; fechaDevolucion.mostrar();
    cout << endl;
}

int Prestamo::getIdPrestamo() const { return idPrestamo; }
int Prestamo::getIdSocio() const { return idSocio; }
int Prestamo::getIdLibro() const { return idLibro; }

/// Archivo
bool Prestamo::guardar() {
    FILE *p = fopen("prestamos.dat", "ab");
    if (p == NULL) return false;
    fwrite(this, sizeof(Prestamo), 1, p);
    fclose(p);
    return true;
}

bool Prestamo::leer(int pos) {
    FILE *p = fopen("prestamos.dat", "rb");
    if (p == NULL) return false;
    fseek(p, pos * sizeof(Prestamo), 0);
    bool leyo = fread(this, sizeof(Prestamo), 1, p);
    fclose(p);
    return leyo;
}
