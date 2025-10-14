#include <iostream>
#include <cstdio>
#include <limits>
#include "Prestamo.h"
using namespace std;

void Prestamo::cargar()
{

    bool entro = false;
    while (!entro)
    {
        cout << "ID Prestamo: ";
        cin >> idPrestamo;
        // Verificar que el ID no exista ya en el archivo, si existe, pedir otro
        // que no sea negativo, mostrar error si es negativo o si ya existe
        if (idPrestamo < 0)
        {
            cout << "Error: El ID no puede ser negativo. Intente nuevamente.\n";
            continue;
        }
        Prestamo obj;
        int pos = 0;
        entro = true;
        while (obj.leer(pos++))
        {
            if (obj.getIdPrestamo() == idPrestamo)
            {
                cout << "Error: El ID ya existe. Intente con otro.\n";
                entro = false;
                break;
            }
        }
    }
    cout << "ID Socio: ";
    cin >> idSocio;
    cout << "ID Libro: ";
    cin >> idLibro;
    cout << "Fecha Prestamo: \n";
    fechaPrestamo.cargar();
    cout << "Fecha Devolucion: \n";
    fechaDevolucion.cargar();
}

void Prestamo::mostrar() const
{
    cout << "Prestamo ID: " << idPrestamo
         << " | Socio: " << idSocio
         << " | Libro: " << idLibro
         << " | Prestado: ";
    fechaPrestamo.mostrar();
    cout << " | Devuelto: ";
    fechaDevolucion.mostrar();
    cout << endl;
}

int Prestamo::getIdPrestamo() const { return idPrestamo; }
int Prestamo::getIdSocio() const { return idSocio; }
int Prestamo::getIdLibro() const { return idLibro; }

/// Archivo
bool Prestamo::guardar()
{
    FILE *p = fopen("prestamos.dat", "ab");
    if (p == NULL)
        return false;
    fwrite(this, sizeof(Prestamo), 1, p);
    fclose(p);
    return true;
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
