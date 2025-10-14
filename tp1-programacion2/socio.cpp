#include <iostream>
#include <cstdio>
#include <limits>
#include "Socio.h"
using namespace std;

void Socio::cargar()
{
    bool entro = false;
    while (!entro)
    {
        cout << "ID Socio: ";
        cin >> idSocio;
        /// verificar que no exista el id, si existe, pedir otro, q sea positivo y sino tire error
        // mostrar mensaje de error si existe y si el numero es negaivo
        if (idSocio < 0)
        {
            cout << "Error: El ID debe ser un numero positivo.\n";
        }
        else if (existeId(idSocio))
        {
            cout << "Error: El ID ya existe. Ingrese otro ID.\n";
        }
        else
        {
            entro = true;
        }
        cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Limpiar el buffer de entrada
    }

    cout << "Nombre: ";
    cin.getline(nombre, 20);
    cout << "Apellido: ";
    cin.getline(apellido, 20);
    cout << "Telefono: ";
    cin.getline(telefono, 15);
    cout << "direccion: ";
    cin.getline(direccion, 50);
    cout << "correo electronico: ";
    cin.getline(correo, 40);
    cout << "fecha de alta del socio: " << endl;
    fechaalta.cargar();
    eliminado = false;
}

void Socio::mostrar() const
{
    if (!eliminado)
    {
        cout << "ID: " << idSocio
             << " | " << nombre << " " << apellido
             << " | Tel: " << telefono
             << " | direccion: " << direccion
             << " | Correo: " << correo
             << " | Fecha alta: ";
        fechaalta.mostrar();
        cout << endl;
    }
}

int Socio::getIdSocio() const { return idSocio; }

bool Socio::getEliminado() const { return eliminado; }

void Socio::setEliminado(bool e) { eliminado = e; }

/// Archivo
bool Socio::guardar()
{
    FILE *p = fopen("socios.dat", "ab");
    if (p == NULL)
        return false;
    fwrite(this, sizeof(Socio), 1, p);
    fclose(p);
    return true;
}

bool Socio::leer(int pos)
{
    FILE *p = fopen("socios.dat", "rb");
    if (p == NULL)
        return false;
    fseek(p, pos * sizeof(Socio), 0);
    bool leyo = fread(this, sizeof(Socio), 1, p);
    fclose(p);
    return leyo;
}

bool Socio::modificar(int pos)
{
    FILE *p = fopen("socios.dat", "rb+");
    if (p == NULL)
        return false;
    fseek(p, pos * sizeof(Socio), 0);
    bool ok = fwrite(this, sizeof(Socio), 1, p);
    fclose(p);
    return ok;
}
bool Socio::existeId(int id)
{
    Socio socios;
    FILE *p = fopen("socios.dat", "rb");
    if (p == NULL)
        return false;

    while (fread(&socios, sizeof(socios), 1, p))
    {
        if (!socios.getEliminado() && socios.getIdSocio() == id)
        {
            fclose(p);
            return true;
        }
    }

    fclose(p);
    return false;
}
