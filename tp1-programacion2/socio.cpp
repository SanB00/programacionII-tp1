#include "socio.h"

#include <cstdio>
#include <iostream>
#include <limits>

using namespace std;
#include "validaciones.cpp"
char* NOMBRE_ARCHIVO = const_cast<char*>("socios.dat");
int Socio::siguienteId = Socio::calcularMaximoId();

// obtener id siguiente y que no se repita en el archivo
int Socio::calcularMaximoId() {
  Socio aux;
  FILE* p = fopen(NOMBRE_ARCHIVO, "rb");
  if (p == nullptr) {
    return 1;
  }

  int maxId = 0;
  while (fread(&aux, sizeof(Socio), 1, p)) {
    if (aux.getIdSocio() > maxId) {
      maxId = aux.getIdSocio();
    }
  }
  fclose(p);
  return ++maxId;
}

void Socio::cargar() {
  cout << "\n *** Alta de un Socio *** \n";
  this->cargarCamposModificables();
  cout << "Fecha de alta del socio: ";
  fechaAlta.cargarFechaDelDia();
  eliminado = false;
  cout << endl;
  this->guardar();
}

void Socio::cargarCamposModificables() {
  cout << "Nombre: ";
  cin.sync();
  cargarCadena(nombre, 30);
  cout << "Apellido: ";
  cargarCadena(apellido, 30);
  cout << "Telefono: ";
  cargarCadena(telefono, 10);
  cout << "Direccion: ";
  cargarCadena(direccion, 50);
  cout << "Correo electronico: ";
  cargarCadena(correo, 40);
}
void Socio::mostrar() const {
  // if (!eliminado) {
  cout << "ID: " << idSocio << " | Nombre: " << this->getNombre()
       << " | Apellido: " << this->getApellido() << " | Telefono: " << telefono
       << " | direccion: " << direccion << " | Correo: " << correo
       << " | Fecha alta: " << fechaAlta.toString()
       << " | Estado eliminado: " << eliminado << endl;
  // }
}

/// Archivo
bool Socio::guardar() {
  cout << "\nGuardando el registro de Socio...";
  FILE* p = fopen("socios.dat", "ab");
  if (p == NULL) return false;
  fwrite(this, sizeof(Socio), 1, p);
  fclose(p);
  cout << "\nSocio guardado con exito! ID: " << this->idSocio << ".\n";
  return true;
}

bool Socio::leer(int pos) {
  FILE* p = fopen("socios.dat", "rb");
  if (p == NULL) return false;
  fseek(p, pos * sizeof(Socio), 0);
  bool leyo = fread(this, sizeof(Socio), 1, p);
  fclose(p);
  return leyo;
}

bool Socio::modificar(int pos) {
  FILE* p = fopen("socios.dat", "rb+");
  if (p == NULL) return false;
  fseek(p, pos * sizeof(Socio), 0);
  bool ok = fwrite(this, sizeof(Socio), 1, p);
  fclose(p);
  return ok;
}
bool Socio::existeId(int id) {
  Socio socios;
  FILE* p = fopen("socios.dat", "rb");
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

bool Socio::modificarRegistroEnArchivo(int posicion, const Socio& datosNuevos) {
  // Abre en modo lectura/escritura binaria
  FILE* pFILE = fopen(NOMBRE_ARCHIVO, "rb+");
  if (pFILE == nullptr) {
    cout << "Error al abrir el archivo " << NOMBRE_ARCHIVO
         << " para modificacion." << endl;
    return false;
  }

  // 1. Calcula el desplazamiento (offset) en bytes
  // Multiplicamos la 'posicion' (índice base 0) por el tamaño del objeto Socio
  long desplazamiento = posicion * sizeof(Socio);

  // 2. Posiciona el puntero del archivo
  // Movemos el puntero 'desplazamiento' bytes desde el inicio (SEEK_SET)
  fseek(pFILE, desplazamiento, SEEK_SET);

  // 3. Escribe  los nuevos datos en esa posición
  // Escribe 1 bloque de tamaño sizeof(Socio) desde la dirección de datosNuevos
  size_t escritos = fwrite(&datosNuevos, sizeof(Socio), 1, pFILE);

  fclose(pFILE);

  if (escritos == 1) {
    return true;
  } else {
    cout << "Error al escribir el registro en la posicion " << posicion << endl;
    return false;
  }
}

int Socio::getCantRegistros() {
  FILE* pFILE = fopen(NOMBRE_ARCHIVO, "rb");
  if (pFILE == nullptr) {
    return -1;
  }
  fseek(pFILE, 0, 2);
  // fseek(pFILE, -sizeof(registro), SEEK_CUR);
  int tamanio = ftell(pFILE);
  fclose(pFILE);
  return tamanio / sizeof(Socio);
}

int Socio::buscarPosicionDeRegistro(int idSocio) {
  Socio obj;
  int posicion = 0;
  FILE* p = fopen(NOMBRE_ARCHIVO, "rb");
  if (p == nullptr) return -1;

  while (fread(&obj, sizeof(Socio), 1, p)) {
    if (obj.getIdSocio() == idSocio) {
      fclose(p);
      return posicion;
    }
    posicion++;
  }
  fclose(p);
  return -1;  // No se encontró el ID
}

void Socio::modificarRegistro() {
  int idBuscado = 0;
  cout << "Ingrese ID del socio a modificar: ";
  cin >> idBuscado;
  cin.ignore();
  int posicion = Socio::buscarPosicionDeRegistro(idBuscado);
  if (posicion < 0) {
    cout << "El socio con ID " << idBuscado << " no existe." << endl;
    return;
  }

  Socio socioExistente = buscar(idBuscado);
  Socio::cargarCamposModificables();  // modifica los campos del objeto this

  // Mantiene el mismo ID y la la fecha de alta original
  this->idSocio = idBuscado;
  this->fechaAlta = socioExistente.getFechaAlta();
  this->eliminado = socioExistente.getEliminado();
  if (Socio::modificarRegistroEnArchivo(posicion, *this)) {
    cout << "Registro de socio modificado exitosamente." << endl;
  } else {
    cout << "Error al modificar el registro de socio." << endl;
  }
}

Socio Socio::buscar(int id) {
  Socio aux, objEncontrado;
  bool comprobado = false;
  FILE* p = fopen(NOMBRE_ARCHIVO, "rb");
  while (fread(&aux, sizeof(Socio), 1, p)) {
    if (aux.getIdSocio() == id) {
      objEncontrado = aux;
      objEncontrado.mostrar();
      comprobado = true;
    }
  }
  if (comprobado == false) {
    cout << "No existe registros de socio con ID: " << id << endl;
    objEncontrado.setIdSocio(ID_NO_ENCONTRADO);
  }
  fclose(p);
  return objEncontrado;
}

void Socio::asignarEstadoDeRegistroComoActivo(bool estadoEsperado) {
  int idBuscado = 0;
  string mensajeAccion = estadoEsperado ? "activar" : "desactivar";
  cout << "Ingrese ID del socio a " << mensajeAccion << ": ";
  cin >> idBuscado;
  cin.ignore();
  int posicion = Socio::buscarPosicionDeRegistro(idBuscado);
  if (posicion < 0) {
    cout << "El socio con ID " << idBuscado << " no existe." << endl;
    return;
  }

  Socio socioExistente = buscar(idBuscado);
  if (socioExistente.getIdSocio() == Socio::ID_NO_ENCONTRADO) {
    cout << "El socio con ID " << idSocio
         << " no existe. Cancelando prestamo..." << endl;
    return;
  }
  if (socioExistente.getEliminado() == !estadoEsperado) {
    cout << "El socio con ID " << idBuscado << " ya se encuentra en el estado "
         << (estadoEsperado ? "activo." : "desactivado.") << endl;
    return;
  }
  *this = socioExistente;
  this->eliminado = !estadoEsperado;
  if (Socio::modificarRegistroEnArchivo(posicion, *this)) {
    cout << "\nSe pudo " << mensajeAccion
         << " el registro exitosamente. Nuevo estado: " << endl;
    this->mostrar();
  } else {
    cout << "Error al " << mensajeAccion << " el registro de socio." << endl;
  }
}
