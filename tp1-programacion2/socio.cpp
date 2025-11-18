#include <iostream>
#include <cstdio>
#include <limits>
#include "socio.h"
using namespace std;
int Socio::siguienteId = 1;
void Socio::cargar() {
    cout << "\n *** Alta de un Socio *** \n";
    cout << "Nombre: ";
    cin.ignore();
    string n;
    std::getline(std::cin, n);
    this->setNombre(n);
    cout << "Apellido: ";
        string a;
    std::getline(std::cin, a);
    this->setApellido(a);

    cout << "Telefono: ";
    cin.getline(telefono, 15);
    cout<<"direccion: ";
    cin.getline (direccion,50);
    cout<<"correo electronico: ";
    cin.getline(correo,40);
    cout<<"fecha de alta del socio: "<<endl;
    fechaalta.cargarFechaDelDia();
    eliminado = false;
}

void Socio::mostrar() const {
    if (!eliminado) {
        cout << "ID: " << idSocio
             << " | " ;
             this->mostrarNombreApellido();
             cout << " | Telefono: " << telefono
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
