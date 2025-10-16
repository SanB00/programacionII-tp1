#include <iostream>
#include <cstdio>
#include <cstring>
#include <limits>
#include "Libros.h"

using namespace std;

void Libros::cargar() {
    bool entro = false;
    while (!entro) {
        cout << "ID Libro: ";
        cin >> idLibro;

        if (cin.fail()) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Entrada invalida. Intenta de nuevo.\n";
        } else if (existeId(idLibro)) {
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Ese ID ya existe. Ingrese uno diferente.\n";
        } else {
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            entro = true;
            cout << "Se ingreso correctamente.\n";
        }
    }

    cout << "Titulo: "; cin.getline(titulo, 50);
    cout << "Autor: "; cin.getline(autor, 30);
    cout << "Editorial: "; cin.getline(editorial, 30);
    cout << "Fecha de alta del libro: "; fechaalta.cargar();
    eliminado = false;
}

void Libros::mostrar() const {
    if (!eliminado) {
        cout << "ID: " << idLibro
             << " | Titulo: " << titulo
             << " | Autor: " << autor
             << " | Editorial: " << editorial
             << " | Fecha de alta "; fechaalta.mostrar();
             cout<<endl;
    }
}

int Libros::getIdLibro() const { return idLibro; }

bool Libros::getEliminado() const { return eliminado; }

void Libros::setEliminado(bool e) { eliminado = e; }

void Libros::buscar(int id){
    bool comprobado = false;
    Libros libro;
    FILE *p =fopen("libros.dat","rb");
    while (fread(&libro,sizeof(libro),1,p)){
        if(libro.getIdLibro()==id){
            libro.mostrar();
            comprobado=true;;
        }
    }

     if (comprobado==false){
        cout<<"no existe id"<<endl;
    }
    fclose(p);
}

/// Archivo
bool Libros::guardar() {
    FILE *p = fopen("libros.dat", "ab");
    if (p == NULL) return false;
    fwrite(this, sizeof(Libros), 1, p);
    fclose(p);
    return true;
}

bool Libros::leer(int pos) {
    FILE *p = fopen("libros.dat", "rb");
    if (p == NULL) return false;
    fseek(p, pos * sizeof(Libros), 0);
    bool leyo = fread(this, sizeof(Libros), 1, p);
    fclose(p);
    return leyo;
}

bool Libros::modificar(int pos) {
    FILE *p = fopen("libros.dat", "rb+");
    if (p == NULL) return false;
    fseek(p, pos * sizeof(Libros), 0);
    bool ok = fwrite(this, sizeof(Libros), 1, p);
    fclose(p);
    return ok;
}
bool Libros::existeId(int id) {
    Libros libro;
    FILE *p = fopen("libros.dat", "rb");
    if (p == NULL) return false;

    while (fread(&libro, sizeof(Libros), 1, p)) {
        if (!libro.getEliminado() && libro.getIdLibro() == id) {
            fclose(p);
            return true;
        }
    }

    fclose(p);
    return false;
}



void Libros::buscarPorAutor() {
    char autorBuscado[30];
    cout << "Ingrese el nombre del autor a buscar: ";

    cin.getline(autorBuscado, 30);
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    FILE *p = fopen("libros.dat", "rb");
    if (p == NULL) {
        cout << "No se pudo abrir el archivo de libros.\n";
        return;
    }

    Libros reg;
    bool encontrado = false;

    cout << "\n=== RESULTADOS DE LA BUSQUEDA ===\n";
    while (fread(&reg, sizeof(Libros), 1, p) == 1) {
        // Coincidencia parcial (si quer�s exacta, usar strcmp)
        if (strstr(reg.getAutor(), autorBuscado) != NULL) {
            reg.mostrar();
            encontrado = true;
        }
    }

    if (!encontrado) {
        cout << "\nNo se encontraron libros de ese autor.\n";
    }

    fclose(p);
}
