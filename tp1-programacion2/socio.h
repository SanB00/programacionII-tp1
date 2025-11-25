#ifndef SOCIO_H
#define SOCIO_H
#include "Persona.cpp"
#include "fecha.h"
class Socio : public Persona {
 private:
  int idSocio;
  static int siguienteId;
  char telefono[10];
  char direccion[50];
  char correo[40];
  Fecha fechaAlta;
  bool eliminado;

 public:
  Socio() : Persona("", "") {
    idSocio = ++siguienteId;
    eliminado = false;
  }
  int getIdSocio() const { return idSocio; }
  bool getEliminado() const { return eliminado; }
  void setEliminado(bool e) { eliminado = e; }

  void cargar();
  void mostrar() const;
  Socio buscar(int id);
  Fecha getFechaAlta() { return fechaAlta; }
  const char* getNombre() const{ return nombre; }
  const char* getApellido() const{ return apellido; }
  /// Manejo de archivo
  bool guardar();
  bool leer(int pos);
  bool modificar(int pos);
  bool existeId(int id);
  void mostrarNombreApellido() { Persona::mostrarNombreApellido(); }
  void modificarRegistro();
  void asignarEstadoDeRegistroComoActivo(bool estadoEsperado);
  bool modificarRegistroEnArchivo(int posicion, const Socio& datosNuevos);
  int getCantRegistros();
  int buscarPosicionDeRegistro(int idSocio);
  void cargarCamposModificables();
};

#endif  // SOCIO_H
