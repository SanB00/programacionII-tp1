#include <iostream>
#include <cstdio>
#include <limits>
#include "socio.h"
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
        }
        else if (existeId(idSocio)) {
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Ese ID ya existe. Ingrese uno diferente.\n";
        }else {
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // limpia todo el buffer
            entro = true;  // v�lida
            cout << "Se ingreso correctamente.\n";
        }
    }

    cout << "Nombre: ";
    cin.getline(nombre, 20);
    cout << "Apellido: ";
    cin.getline(apellido, 20);
    
    cout << "Telefono: ";
    cin.getline(telefono, 15);
    cout<<"direccion: ";
    cin.getline (direccion,50);
    cout<<"correo electronico: ";
    cin.getline(correo,40);
    cout<<"fecha de alta del socio: "<<endl;
    fechaalta.cargar();
    eliminado = false;
}

void Socio::mostrar() const {
    if (!eliminado) {
        cout << "ID: " << idSocio
             << " | " << nombre << " " << apellido
             << " | Tel: " << telefono
             << " | direccion: " << direccion
             << " | Correo: " << correo
             << " | Fecha alta: ";fechaalta.mostrar();
             cout<<endl;

    }
}

int Socio::getIdSocio() const { return idSocio; }

bool Socio::getEliminado() const { return eliminado; }

void Socio::setEliminado(bool e) { eliminado = e; }

void Socio::buscar(int id){
    Socio socios;
    bool comprobado = false;
    FILE *p =fopen("socios.dat","rb");
    while (fread(&socios,sizeof(socios),1,p)){
        if(socios.getIdSocio()==id){
           socios.mostrar();
           comprobado = true;}
        }
    if (comprobado==false){
        cout<<"no existe id"<<endl;
    }
    fclose(p);
}


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
bool Socio::existeId(int id) {
    Socio socios;
    FILE *p = fopen("socios.dat", "rb");
    if (p == NULL) return false;

    while (fread(&socios, sizeof(socios), 1, p)) {
        if (!socios.getEliminado() && socios.getIdSocio() == id) {
            fclose(p);
            return true;
        }
    }

    fclose(p);
    return false;
}
