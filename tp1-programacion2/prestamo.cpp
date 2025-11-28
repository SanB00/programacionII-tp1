#include "prestamo.h"

#include <cstdio>
#include <iostream>
#include <limits>

#include "Validaciones.cpp"
#include "fecha.h"
#include "libros.h"
#include "socio.h"

const int ID_NO_ENCONTRADO = -1;

int Prestamo::siguienteId = Prestamo::calcularMaximoId();

int Prestamo::calcularMaximoId() {
  Prestamo aux;
  FILE* p = fopen("prestamos.dat", "rb");
  if (p == nullptr) {
    return 1;
  }

  int maxId = 0;
  while (fread(&aux, sizeof(Prestamo), 1, p)) {
    if (aux.getIdPrestamo() > maxId) {
      maxId = aux.getIdPrestamo();
    }
  }
  fclose(p);
  return ++maxId;
}
bool buscarYMostrarLibroPrestado(int idLibro);
void Prestamo::cargar() {
  cout << "--- Alta de un Prestamo --- \n";
  cout << "ID Socio: ";
  cin >> idSocio;
  cout << "Verificando existencia de socio..." << endl;
  Socio aux, objSocio;
  objSocio = aux.buscar(idSocio);
  if (objSocio.getIdSocio() == ID_NO_ENCONTRADO) {
    cout << "El socio con ID \"" << idSocio
         << "\" no existe. Cancelando prestamo..." << endl;
    return;
  }
  if (objSocio.getEliminado()) {
    cout << "El socio con ID " << idSocio
         << " esta eliminado. Cancelando prestamo..." << endl;
    return;
  }

  cout << "ID Libro: ";
  cin >> idLibro;
  if (!buscarYMostrarLibroPrestado(idLibro)) {
    return;
  }
  cout << "Fecha Prestamo (1: Fecha manual, 0: Fecha del dia): ";
  int opcionFechaPrestamo = 0;
  cin.ignore();
  cin >> opcionFechaPrestamo;
  if (opcionFechaPrestamo == 1) {
    fechaPrestamo.cargarFechaManual();
  } else {
    cout << "\nFecha Prestamo: ";
    fechaPrestamo.cargarFechaDelDia();
  }
  cout << "\nFecha Devolucion: \n";
  bool laFechaDevolucionEsAnteriorAlPrestamo = false;
  do {
    fechaDevolucion.cargarFechaManual();
    if (fechaDevolucion.esAnteriorA(fechaPrestamo)) {
      cout << "La fecha de devolucion no puede ser anterior a la fecha de "
              "prestamo. Intente nuevamente.\n";
      laFechaDevolucionEsAnteriorAlPrestamo = true;
    } else {
      laFechaDevolucionEsAnteriorAlPrestamo = false;
    }
  } while (laFechaDevolucionEsAnteriorAlPrestamo);

  this->guardar();
}

void Prestamo::mostrar() const {
  cout << "Prestamo ID: " << idPrestamo << " | Socio: " << idSocio
       << " | Libro: " << idLibro << " | Prestado: ";
  fechaPrestamo.mostrar();
  cout << " | Devuelto: ";
  fechaDevolucion.mostrar();
  cout << endl;
}

bool Prestamo::guardar() {
  cout << "\nGuardado Prestamo en archivo...\n";
  FILE* p = fopen("prestamos.dat", "ab");
  if (p == NULL) return false;
  fwrite(this, sizeof(Prestamo), 1, p);
  fclose(p);
  cout << "Prestamo guardado con exito! ID: " << this->idPrestamo << ".\n";
  this->mostrar();
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
    cout << "No existen registros con el ID: " << id << endl;
  }
  fclose(p);
}
Prestamo Prestamo::buscar(int id) {
  Prestamo aux, objEncontrado;
  bool comprobado = false;
  FILE* p = fopen("prestamos.dat", "rb");
  while (fread(&aux, sizeof(Prestamo), 1, p)) {
    if (aux.getIdPrestamo() == id) {
      objEncontrado = aux;
      // objEncontrado.mostrar();
      comprobado = true;
    }
  }
  if (comprobado == false) {
    cout << "No existe el registro de prestamos con ID: " << id << endl;
    objEncontrado.setIdPrestamo(ID_NO_ENCONTRADO);
  }
  fclose(p);
  return objEncontrado;
}
bool grabarRegistroEnArchivo(Prestamo obj, const char* nombreArchivo = "") {
  FILE* p = fopen(nombreArchivo, "ab");
  if (p == nullptr) {
    return false;
  }
  bool escribio = fwrite(&obj, sizeof obj, 1, p);
  fclose(p);
  return escribio;
}
void Prestamo::bajaFisica() {
  cout << "ATENCION: Si tuvo un error registrando un prestamo puede eliminarlo "
          "aunque tenga en cuenta que es permanentemente"
          "\nDesea continuar? (1 = SI, 0 = NO): ";
  int confirmaEliminacion;
  cin >> confirmaEliminacion;

  if (confirmaEliminacion == 0) {
    cout << "Se cancela la eliminacion. Volviendo al menu..." << endl;
    return;
  }

  cout << "Ingrese el ID del registro de prestamo que desea ELIMINAR "
          "PERMANENTEMENTE (o un ID inexistente para volver al menu): ";
  int idPrestamoAEliminar;
  cin >> idPrestamoAEliminar;
  Prestamo objEncontrado = buscar(idPrestamoAEliminar);
  if (objEncontrado.getIdPrestamo() == ID_NO_ENCONTRADO) {
    cout << "El prestamo con ID " << idPrestamoAEliminar << " no existe..."
         << endl;
    return;
  }

  cout << "Eliminando registro con ID: " << idPrestamoAEliminar << endl;
  objEncontrado.mostrar();
  // Creando archivo temporal sin el registro a eliminar
  bool huboErrores = false;
  Prestamo objArchivoOriginal;
  FILE* p = fopen("prestamos.dat", "rb");
  int registrosLeidos, registrosGuardados = 0;
  while (fread(&objArchivoOriginal, sizeof(Prestamo), 1, p)) {
    registrosLeidos++;
    if (objArchivoOriginal.getIdPrestamo() != idPrestamoAEliminar) {
      if (grabarRegistroEnArchivo(objArchivoOriginal, "temp.dat")) {
        registrosGuardados++;
      } else {
        cout << "Error al copiar el registro con ID: "
             << objArchivoOriginal.getIdPrestamo() << endl;
        huboErrores = true;
      }
    }
  }
  fclose(p);
  cout << "\nINFO: Registros leidos: " << registrosLeidos - 1
       << " | Registros guardados: " << registrosGuardados << endl;
  if (huboErrores) {
    cout << "No se completo la eliminacion debido a errores." << endl;
    remove("temp.dat");
    return;
  }
  // Reemplazar archivo original
  remove("prestamos.dat");
  rename("temp.dat", "prestamos.dat");
  cout << "Se elimino con exito el prestamo con id: " << idPrestamo << endl;
}

void buscarPorIdSocioYMostrar(int id) {
  bool comprobado = false;
  Prestamo prestamo;
  FILE* p = fopen("prestamos.dat", "rb");
  while (fread(&prestamo, sizeof(Prestamo), 1, p)) {
    if (prestamo.getIdSocio() == id) {
      prestamo.mostrar();
      comprobado = true;
    }
  }

  if (comprobado == false) {
    cout << "No existen registros con el ID:" << id << endl;
  }
  fclose(p);
}

bool buscarYMostrarLibroPrestado(int idLibro) {
  Libros auxLibro, objLibro;
  objLibro = auxLibro.buscar(idLibro);
  if (objLibro.getIdLibro() == ID_NO_ENCONTRADO) {
    cout << "El libro con ID \"" << idLibro
         << "\" no existe. "
            "Cancelando prestamo..."
         << endl;
    return false;
  }
  if (objLibro.getEliminado()) {
    cout << "El libro con ID " << idLibro
         << " esta eliminado. Cancelando prestamo..." << endl;
    return false;
  }
  return true;
}

bool Prestamo::leer(int pos) {
  FILE* p = fopen("prestamos.dat", "rb");
  if (p == NULL) return false;
  fseek(p, pos * sizeof(Prestamo), 0);
  bool leyo = fread(this, sizeof(Prestamo), 1, p);
  fclose(p);
  return leyo;
}

void Prestamo::listar() {
  cout << "\n--- LISTADO ---\n\n";
  Prestamo obj;
  int pos = 0;
  while (this->leer(pos++)) {
    this->mostrar();
    buscarYMostrarLibroPrestado(this->getIdLibro());
    cout << "-----------------------------------\n";
  }
  if (pos == 1) {
    cout << "No hay prestamos cargados.\n";
  }
  cout << "\n--- " << pos - 1 << " registros ---\n\n";
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
///
///
///
void Prestamo::buscarLibroMasPrestado() {
  const int MAX_LIBROS = 1000;
  int ids[MAX_LIBROS];
  int cant[MAX_LIBROS];
  int cantUnica = 0;

  for (int i = 0; i < MAX_LIBROS; i++) {
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
    int id = aux.getIdLibro();
    bool encontrado = false;
    for (int i = 0; i < cantUnica; i++) {
      if (ids[i] == id) {
        cant[i]++;
        encontrado = true;
        break;
      }
    }
    if (!encontrado) {
      if (cantUnica >= MAX_LIBROS) {
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
  cout << "Libro más prestado tiene el ID: " << idMax << " (" << cant[maxIdx]
       << " prestamos):" << endl;
  buscarYMostrarLibroPrestado(idMax);
}
///
///
///
int Prestamo::cantidadPrestamosPorMes(int mes, int anio) {
  int contador = 0;
  FILE* p = fopen("prestamos.dat", "rb");
  if (p == NULL) {
    cout << "No se pudo abrir el archivo de prestamos." << endl;
    return 0;
  }

  Prestamo aux;
  while (fread(&aux, sizeof(Prestamo), 1, p)) {
    if (aux.fechaPrestamo.getMes() == mes &&
        aux.fechaPrestamo.getAnio() == anio) {
      contador++;
    }
  }

  fclose(p);
  return contador;
}
///
///
///
void Prestamo::cantidadPrestamosPorAnio() {
  int anio = 0;
  int totalPrestado = 0;
  cout << "Ingrese el anio para el informe: ";
  cin >> anio;
  if (anio >= 2100 || anio <= 1900) {
    cout << "Anio invalido. Por favor ingrese un anio entre 1900 y 2100."
         << endl;
    return;
  } else {
    cout << "Anio valido." << endl;
  }
  cout << "Cantidad de prestamos por mes en el anio " << anio << ":\n";
  for (int mes = 1; mes <= 12; mes++) {
    int cantidad = Prestamo::cantidadPrestamosPorMes(mes, anio);
    cout << "Mes " << mes << " (" << Fecha::mostrarMesEnLetras(mes)
         << ") : " << cantidad << " prestamos\n ";
    totalPrestado += cantidad;
  }
  cout << "Total de prestamos en el anio " << anio << ": " << totalPrestado
       << " prestamos\n";
}

void Prestamo::cantidadPrestamosPorAnioYMes() {
  int anio = 0, mes = 0, dia = 1;
  cout << "Ingrese el anio para el informe: ";
  cin >> anio;
  cout << "Ingrese el mes para el informe: ";
  cin >> mes;
  Fecha fecha(dia, mes, anio);
  if (!fecha.esUnaFechaValida()) {
    cout << "Fecha invalida. Por favor ingrese una fecha valida." << endl;
    return;
  }

  int cantidad = Prestamo::cantidadPrestamosPorMes(mes, anio);
  cout << "Anio " << anio << " Mes " << mes << ": " << cantidad
       << " prestamos\n";
}
void Prestamo::cantidadPrestamosPorSocio() {
  int idSocio = 0;
  cout << "--- Informe de prestamos a un socio --- ";
  cout << "\nID Socio: ";
  cin >> idSocio;
  cin.ignore();
  cout << "Verificando existencia de socio..." << endl;
  Socio aux, objSocio;
  objSocio = aux.buscar(idSocio);
  if (objSocio.getIdSocio() == ID_NO_ENCONTRADO) {
    cout << "El socio con ID " << idSocio << " no existe..." << endl;
    return;
  }
  if (objSocio.getEliminado()) {
    cout << "El socio con ID " << idSocio
         << " aparece como eliminado pero estos fueron sus prestamos: " << endl;
  }

  cout << endl << endl;

  int cantidad = Prestamo::cantidadPrestamosPorSocioArchivo(idSocio);
  cout << "Cantidad de prestamos del socio con ID " << idSocio << ": "
       << cantidad << " prestamos\n";

  buscarPorIdSocioYMostrar(idSocio);
}

int Prestamo::cantidadPrestamosPorSocioArchivo(int idSocio) {
  int contador = 0;
  FILE* p = fopen("prestamos.dat", "rb");
  if (p == NULL) {
    cout << "No se pudo abrir el archivo de prestamos." << endl;
    return 0;
  }

  Prestamo aux;
  while (fread(&aux, sizeof(Prestamo), 1, p)) {
    if (aux.getIdSocio() == idSocio) {
      contador++;
    }
  }

  fclose(p);
  return contador;
}
///
