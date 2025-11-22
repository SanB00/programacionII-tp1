#include "libros.h"

#include <cstdio>
#include <cstring>
#include <iostream>
#include <limits>

using namespace std;

int Libros::siguienteId = 1;

void Libros::cargar() {
  cout << "\n *** Alta de un Libro *** \n";
  cout << "Ingrese el titulo del libro: ";
  cin.ignore();
  cin.getline(titulo, 50);
  cout << "Ingrese el autor del libro: ";
  cin.getline(autor, 30);
  cout << "Ingrese la editorial del libro: ";
  cin.getline(editorial, 30);
  fechaalta.cargarFechaDelDia();
  eliminado = false;
}

void Libros::mostrar() const {
  if (!eliminado) {
    cout << "ID: " << idLibro << " | Titulo: " << titulo
         << " | Autor: " << autor << " | Editorial: " << editorial
         << " | Fecha de alta ";
    fechaalta.mostrar();
    cout << endl;
  }
}

/// Archivo
bool Libros::guardar() {
  FILE* p = fopen("libros.dat", "ab");
  if (p == NULL) return false;
  fwrite(this, sizeof(Libros), 1, p);
  fclose(p);

  cout << "Libro guardado con ID" << this->idLibro << ".\n";

  return true;
}

bool Libros::leer(int pos) {
  FILE* p = fopen("libros.dat", "rb");
  if (p == NULL) return false;
  fseek(p, pos * sizeof(Libros), 0);
  bool leyo = fread(this, sizeof(Libros), 1, p);
  fclose(p);
  return leyo;
}

bool Libros::modificar(int pos) {
  FILE* p = fopen("libros.dat", "rb+");
  if (p == NULL) return false;
  fseek(p, pos * sizeof(Libros), 0);
  bool ok = fwrite(this, sizeof(Libros), 1, p);
  fclose(p);
  return ok;
}
bool Libros::existeId(int id) {
  Libros libro;
  FILE* p = fopen("libros.dat", "rb");
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

///
///
///
void Libros::buscarPorId(int id) {
  bool comprobado = false;
  Libros libro;
  FILE* p = fopen("libros.dat", "rb");
  while (fread(&libro, sizeof(libro), 1, p)) {
    if (libro.getIdLibro() == id) {
      libro.mostrar();
      comprobado = true;
      ;
    }
  }

  if (comprobado == false) {
    cout << "No hay resultados para el ID ingresado: " << id << endl;
  }
  fclose(p);
}

void Libros::buscarPorAutor() {
  char autorBuscado[30];
  cout << "Ingrese el nombre del autor a buscar: ";

  cin.ignore();
  cin.getline(autorBuscado, 30);

  FILE* p = fopen("libros.dat", "rb");
  if (p == NULL) {
    cout << "No se pudo abrir el archivo de libros.\n";
    return;
  }

  Libros reg;
  bool encontrado = false;

  cout << "\n=== RESULTADOS DE LA BUSQUEDA ===\n";
  while (fread(&reg, sizeof(Libros), 1, p) == 1) {
    if (strstr(reg.getAutor(), autorBuscado) != NULL) {
      reg.mostrar();
      encontrado = true;
    }
  }

  if (!encontrado) {
    cout << "\nNo se encontraron libros de ese autor: \""<<autorBuscado<<"\".\n";
  }

  fclose(p);
}

void Libros::buscarPorEditorial() {
  char editorialBuscada[30];
  cout << "Ingrese el nombre de la editorial a buscar: ";
  cin.ignore();  // limpiar buffer antes de getline
  cin.getline(editorialBuscada, 30);

  FILE* p = fopen("libros.dat", "rb");
  if (p == NULL) {
    cout << "No se pudo abrir el archivo de libros.\n";
    return;
  }

  Libros reg;
  bool encontrado = false;

  cout << "\n=== RESULTADOS DE LA BUSQUEDA ===\n";
  while (fread(&reg, sizeof(Libros), 1, p) == 1) {
    // compara directamente con el campo 'editorial'
    if (strstr(reg.editorial, editorialBuscada) != NULL) {
      reg.mostrar();
      encontrado = true;
    }
  }

  if (!encontrado) {
    cout << "\nNo se encontraron libros de esa editorial: \""<<editorialBuscada<<"\".\n";
  }

  fclose(p);
}

void Libros::buscarPorTitulo() {
  char tituloBuscado[50];
  cout << "Ingrese el titulo del libro a buscar: ";
  cin.ignore();
  cin.getline(tituloBuscado, 50);

  FILE* p = fopen("libros.dat", "rb");
  if (p == NULL) {
    cout << "No se pudo abrir el archivo de libros.\n";
    return;
  }

  Libros reg;
  bool encontrado = false;

  cout << "\n=== RESULTADOS DE LA BUSQUEDA ===\n";
  while (fread(&reg, sizeof(Libros), 1, p) == 1) {
    if (strstr(reg.titulo, tituloBuscado) != NULL) {
      reg.mostrar();
      encontrado = true;
    }
  }

  if (!encontrado) {
    cout << "\nNo se encontraron libros con ese titulo.\n";
  }

  fclose(p);
}
