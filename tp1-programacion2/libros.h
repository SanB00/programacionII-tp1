#ifndef LIBROS_H
#define LIBROS_H
#include "fecha.h"
#include <cstring>

class Libros {
 private:
  int idLibro;
  static int siguienteId;
  char titulo[50];
  char autor[30];
  char editorial[30];
  int stock;
  bool eliminado;
  Fecha fechaAlta;

 public:
  const static int ID_NO_ENCONTRADO = -1;
  ~Libros() = default;
  Libros() {
    idLibro = siguienteId;
    Libros::siguienteId++;
    eliminado = false;
  }
  Libros(char* tit, char* aut, char* edi, int stk, Fecha fecha)
      : fechaAlta(fecha) {
    idLibro = siguienteId;
    Libros::siguienteId++;
    strncpy(titulo, tit, sizeof(titulo) - 1);
    titulo[sizeof(titulo) - 1] = '\0';
    // autor = "";
    strncpy(editorial, edi, sizeof(editorial) - 1);
    editorial[sizeof(editorial) - 1] = '\0';
    stock = stk;
    fechaAlta = fecha;
    eliminado = false;
  }
  static int calcularMaximoId();

  void cargar();
  void mostrar() const;
  int getIdLibro() const { return idLibro; }
  void setIdLibro(int id) { idLibro = id; }
  const char* getAutor() const { return autor; }
  const char* getEditorial() const { return editorial; }
  const char* getTitulo() const { return titulo; }
  bool getEliminado() const { return eliminado; }
  void setEliminado(bool e) { eliminado = e; }
  Fecha getFechaAlta() { return fechaAlta; }

  static void buscarPorId(int id);
  static void buscarPorAutor();
  static void buscarPorEditorial();
  static void buscarPorTitulo();

  /// Manejo de archivo
  bool guardar();
  bool leer(int pos);
  bool modificar(int pos);
  bool existeId(int id);
  Libros buscar(int id);
  void modificarRegistro();
  void asignarEstadoDeRegistroComoActivo(bool estadoEsperado);
  bool modificarRegistroEnArchivo(int posicion, const Libros& datosNuevos);
  int getCantRegistros();
  int buscarPosicionDeRegistro(int idLibro);
  void cargarCamposModificables();
};

#endif  // LIBROS_H
