#include <iostream>
#include <cstdio>
#include <limits>
#include "prestamo.h"
using namespace std;

void Prestamo::cargar() {

    bool entro = false;
    while (!entro) {
        cout << "ID Prestamo: ";
        cin >> idPrestamo;
        FILE *p = fopen("prestamos.dat", "rb");
        if (p == NULL)
        {
            entro = true;
            break;
        }
        Prestamo prestamo;
        bool existe = false;
        while (fread(&prestamo, sizeof(Prestamo), 1, p))
        {
            if (prestamo.getIdPrestamo() == idPrestamo)
            {
                existe = true;
                cout << "El ID ya existe. Ingrese otro ID.\n";
                break;
            }
        }
        if (!existe)
            entro = true;
        fclose(p);
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
    cout << "ID Socio: ";
    cin >> idSocio;
    cout << "ID Libro: ";
    cin >> idLibro;
    cout << "Fecha Prestamo: \n";
    fechaPrestamo.cargarFechaDelDia();
    cout << "Fecha Devolucion: \n";
    fechaDevolucion.cargarFechaManual();
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
    if (p == NULL)
        return false;
    fwrite(this, sizeof(Prestamo), 1, p);
    fclose(p);
    return true;
}

void Prestamo::buscar(int id)
{
    bool comprobado = false;
    Prestamo prestamo;
    FILE *p = fopen("prestamos.dat", "rb");
    while (fread(&prestamo, sizeof(prestamo), 1, p))
    {
        if (prestamo.getIdPrestamo() == id)
        {
            prestamo.mostrar();
            comprobado = true;
        }
    }

    if (comprobado == false)
    {
        cout << "no existe el id:" << id << endl;
    }
    fclose(p);
}

bool Prestamo::leer(int pos)
{
    FILE *p = fopen("prestamos.dat", "rb");
    if (p == NULL)
        return false;
    fseek(p, pos * sizeof(Prestamo), 0);
    bool leyo = fread(this, sizeof(Prestamo), 1, p);
    fclose(p);
    return leyo;
}
