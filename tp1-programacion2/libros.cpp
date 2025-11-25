#include "libros.h"

#include <cstdio>
#include <cstring>
#include <iostream>
#include <limits>

#include "Validaciones.cpp"

using namespace std;

int Libros::siguienteId = Libros::calcularMaximoId();

int Libros::calcularMaximoId() {
  Libros aux;
  FILE* p = fopen("libros.dat", "rb");
  if (p == nullptr) {
    return 1;
  }

  int maxId = 0;
  while (fread(&aux, sizeof(Libros), 1, p)) {
    if (aux.getIdLibro() > maxId) {
      maxId = aux.getIdLibro();
    }
  }
  fclose(p);
  return ++maxId;
}

void Libros::cargar() {
  cout << "\n *** Alta de un Libro *** \n";
  this->cargarCamposModificables();
  cout << "Fecha de alta: ";
  fechaAlta.cargarFechaDelDia();
  eliminado = false;

  this->guardar();
  // this->mostrar();
}

void Libros::cargarCamposModificables() {
  cout << "Ingrese el titulo del libro: ";
  cin.sync();  // Limpiar el buffer de entrada antes de getline '\n'
  cargarCadena(titulo, 50);
  cout << "Ingrese el autor del libro: ";
  cargarCadena(autor, 30);
  cout << "Ingrese la editorial del libro: ";
  cargarCadena(editorial, 30);
  stock = 0;
  // cout << "Ingrese el stock del libro: ";
  // do {
  //   cin >> stock;
  //   if (stock < 0) {
  //     cout << "El stock no puede ser negativo. Intente nuevamente: ";
  //   }
  // } while (stock < 0);
}
void Libros::mostrar() const {
  // if (!eliminado) {
  cout << "ID: " << idLibro << " | Titulo: " << titulo << " | Autor: " << autor
       << " | Editorial: " << editorial
       << " | Fecha de alta: " << fechaAlta.toString()
       << " | Estado eliminado: " << eliminado << endl;

  // cout << "ID: " << idLibro << " | Titulo: " << titulo << " | Autor: " <<
  // autor
  //      << " | Editorial: " << editorial << " | Stock: " << stock
  //      << " | Fecha de alta ";
  //}
}

/// Archivo
bool Libros::guardar() {
  cout << "\nGuardando el registro de libro...";
  FILE* p = fopen("libros.dat", "ab");
  if (p == NULL) return false;
  fwrite(this, sizeof(Libros), 1, p);
  fclose(p);

  cout << "\nLibro guardado con ID " << this->idLibro << ".\n";

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
  cargarCadena(autorBuscado, 30);

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
    cout << "\nNo se encontraron libros de ese autor: \"" << autorBuscado
         << "\".\n";
  }

  fclose(p);
}

void Libros::buscarPorEditorial() {
  char editorialBuscada[30];
  cout << "Ingrese el nombre de la editorial a buscar: ";
  cargarCadena(editorialBuscada, 30);
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
    cout << "\nNo se encontraron libros de esa editorial: \""
         << editorialBuscada << "\".\n";
  }

  fclose(p);
}

void Libros::buscarPorTitulo() {
  char tituloBuscado[50];
  cout << "Ingrese el titulo del libro a buscar: ";
  cargarCadena(tituloBuscado, 50);

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
///
///
///

bool Libros::modificarRegistroEnArchivo(int posicion,
                                        const Libros& datosNuevos) {
  // Abre en modo lectura/escritura binaria
  FILE* pFILE = fopen("libros.dat", "rb+");
  if (pFILE == nullptr) {
    cout << "Error al abrir el archivo " << "libros.dat"
         << " para modificacion." << endl;
    return false;
  }

  // 1. Calcular el desplazamiento (offset) en bytes. Multiplicamos la
  // 'posicion' (índice base 0) por el tamaño del objeto Libros
  long desplazamiento = posicion * sizeof(Libros);

  // 2. Posicionar el puntero del archivo. Movemos el puntero 'desplazamiento'
  // bytes desde el inicio (SEEK_SET)
  fseek(pFILE, desplazamiento, SEEK_SET);

  // 3. Escribir los nuevos datos en esa posición Escribe 1 bloque de tamaño
  // sizeof(Libros) desde la dirección de datosNuevos
  size_t escritos = fwrite(&datosNuevos, sizeof(Libros), 1, pFILE);

  fclose(pFILE);

  if (escritos == 1) {
    return true;  // Éxito
  } else {
    cout << "Error al escribir el registro en la posicion " << posicion << endl;
    return false;  // Error de escritura
  }
}

int Libros::getCantRegistros() {
  FILE* pFILE = fopen("libros.dat", "rb");
  if (pFILE == nullptr) {
    return -1;
  }
  fseek(pFILE, 0, 2);
  // fseek(pFILE, -sizeof(registro), SEEK_CUR);
  int tamanio = ftell(pFILE);
  fclose(pFILE);
  return tamanio / sizeof(Libros);
}

int Libros::buscarPosicionDeRegistro(int idLibro) {
  Libros obj;
  int posicion = 0;
  FILE* p = fopen("libros.dat", "rb");
  if (p == nullptr) return -1;

  while (fread(&obj, sizeof(Libros), 1, p)) {
    if (obj.getIdLibro() == idLibro) {
      fclose(p);
      return posicion;  // Retorna la posición (índice base 0)
    }
    posicion++;  // Incrementa la posición por cada registro leído
  }
  fclose(p);
  return -1;  // No se encontró el ID
}

void Libros::modificarRegistro() {
  int idBuscado = 0;
  cout << "Ingrese ID del libro a modificar: ";
  cin >> idBuscado;
  cin.ignore();
  int posicion = Libros::buscarPosicionDeRegistro(idBuscado);
  if (posicion < 0) {
    cout << "El libro con ID " << idBuscado << " no existe." << endl;
    return;
  }

  Libros registroExistente = buscar(idBuscado);
  this->cargarCamposModificables();  // modifica los campos del objeto this

  // Mantener el mismo ID y la la fecha de alta original
  this->idLibro = idBuscado;
  this->fechaAlta = registroExistente.getFechaAlta();
  this->eliminado = registroExistente.getEliminado();
  if (Libros::modificarRegistroEnArchivo(posicion, *this)) {
    cout << "Registro de libro modificado exitosamente." << endl;
  } else {
    cout << "Error al modificar el registro de libro." << endl;
  }
}

Libros Libros::buscar(int id) {
  Libros aux, objEncontrado;
  bool comprobado = false;
  FILE* p = fopen("libros.dat", "rb");
  while (fread(&aux, sizeof(Libros), 1, p)) {
    if (aux.getIdLibro() == id) {
      objEncontrado = aux;
      objEncontrado.mostrar();
      comprobado = true;
    }
  }
  if (comprobado == false) {
    cout << "No hay registro de libro con ID: " << id << endl;
    objEncontrado.setIdLibro(ID_NO_ENCONTRADO);
  }
  fclose(p);
  return objEncontrado;
}

void Libros::asignarEstadoDeRegistroComoActivo(bool estadoEsperado) {
  int idBuscado = 0;
  string mensajeAccion = estadoEsperado ? "activar" : "desactivar";
  cout << "Ingrese ID del libro a " << mensajeAccion << ": ";
  cin >> idBuscado;
  cin.ignore();
  int posicion = Libros::buscarPosicionDeRegistro(idBuscado);
  if (posicion < 0) {
    cout << "El libro con ID " << idBuscado << " no existe." << endl;
    return;
  }

  Libros libroExistente = buscar(idBuscado);
  if (libroExistente.getIdLibro() == Libros::ID_NO_ENCONTRADO) {
    cout << "El libro con ID " << idBuscado
         << " no existe. Cancelando prestamo..." << endl;
    return;
  }
  if (libroExistente.getEliminado() == !estadoEsperado) {
    cout << "El libro con ID " << idBuscado << " ya se encuentra en el estado "
         << (estadoEsperado ? "activo." : "desactivado.") << endl;
    return;
  }
  *this = libroExistente;
  this->eliminado = !estadoEsperado;
  if (Libros::modificarRegistroEnArchivo(posicion, *this)) {
    cout << "Se pudo " << mensajeAccion
         << " el registro exitosamente. Nuevo estado" << endl;
    this->mostrar();
  } else {
    cout << "Error al " << mensajeAccion << " el registro de libro." << endl;
  }
}
