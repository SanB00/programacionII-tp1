#include "prestamo.h"

#include <cstdio>
#include <iostream>
#include <limits>

#include "socio.h"
using namespace std;

void Prestamo::cargar() {
  bool entro = false;
  cout << "ID Socio: ";
  cin >> idSocio;
  cout << "Verificando existencia de socio..." << endl;
  // Socio::buscar(idSocio);

  cout << "ID Libro: ";
  cin >> idLibro;
  cout << "Fecha Prestamo: \n";
  fechaPrestamo.cargarFechaDelDia();
  cout << "Fecha Devolucion: \n";
  fechaDevolucion.cargarFechaManual();
}

void Prestamo::mostrar() const {
  cout << "Prestamo ID: " << idPrestamo << " | Socio: " << idSocio
       << " | Libro: " << idLibro << " | Prestado: ";
  fechaPrestamo.mostrar();
  cout << " | Devuelto: ";
  fechaDevolucion.mostrar();
  cout << endl;
}

int Prestamo::getIdPrestamo() const { return idPrestamo; }
int Prestamo::getIdSocio() const { return idSocio; }
int Prestamo::getIdLibro() const { return idLibro; }

bool Prestamo::guardar() {
  FILE* p = fopen("prestamos.dat", "ab");
  if (p == NULL) return false;
  fwrite(this, sizeof(Prestamo), 1, p);
  cout << "Prestamo guardado con exito.\n";
  fclose(p);
  return true;
}

void Prestamo::buscarPorId(int id) {
  bool comprobado = false;
  Prestamo prestamo;
  FILE* p = fopen("prestamos.dat", "rb");
  while (fread(&prestamo, sizeof(prestamo), 1, p)) {
    if (prestamo.getIdPrestamo() == id) {
      prestamo.mostrar();
      comprobado = true;
    }
  }

  if (comprobado == false) {
    cout << "No existen registros con el id:" << id << endl;
  }
  fclose(p);
}

bool Prestamo::leer(int pos) {
  FILE* p = fopen("prestamos.dat", "rb");
  if (p == NULL) return false;
  fseek(p, pos * sizeof(Prestamo), 0);
  bool leyo = fread(this, sizeof(Prestamo), 1, p);
  fclose(p);
  return leyo;
}
///
///
///
///
void Prestamo::buscarSocioConMasLibros() {
  const int MAX_SOCIOS = 1000;
  int ids[MAX_SOCIOS];
  int cant[MAX_SOCIOS];
  int cantUnica = 0;

  for (int i = 0; i < MAX_SOCIOS; i++) {
    ids[i] = 0;
    cant[i] = 0;
  }

  FILE* p = fopen("prestamos.dat", "rb");
  if (p == NULL) {
    cout << "No se pudo abrir el archivo de prestamos." << endl;
    return;
  }

  Prestamo aux;
  while (fread(&aux, sizeof(Prestamo), 1, p)) {
    int id = aux.getIdSocio();
    bool encontrado = false;
    for (int i = 0; i < cantUnica; i++) {
      if (ids[i] == id) {
        cant[i]++;
        encontrado = true;
        break;
      }
    }
    if (!encontrado) {
      if (cantUnica >= MAX_SOCIOS) {
        continue;
      }
      ids[cantUnica] = id;
      cant[cantUnica] = 1;
      cantUnica++;
    }
  }

  fclose(p);

  if (cantUnica == 0) {
    cout << "No hay prestamos registrados." << endl;
    return;
  }

  int maxIdx = 0;
  for (int i = 1; i < cantUnica; i++) {
    if (cant[i] > cant[maxIdx]) maxIdx = i;
  }

  int idMax = ids[maxIdx];
  cout << "Socio con más libros prestados (" << cant[maxIdx]
       << " prestamos):" << endl;
  Socio s;
  s.buscar(idMax);
}
