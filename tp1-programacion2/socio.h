#ifndef SOCIO_H
#define SOCIO_H
#include "Persona.cpp"
#include "fecha.h"
class Socio : public Persona {
 private:
  int idSocio;
  static int siguienteId;
  char telefono[15];
  char direccion[50];
  char correo[40];
  Fecha fechaalta;
  bool eliminado;

 public:
  Socio() : Persona("", "") {
    idSocio = ++siguienteId;;
    eliminado = false;
  }
  void cargar();
  void mostrar() const;
  int getIdSocio() const;
  bool getEliminado() const;
  void setEliminado(bool e);
  void buscar(int id);

  /// Manejo de archivo
  bool guardar();
  bool leer(int pos);
  bool modificar(int pos);
  bool existeId(int id);
  void mostrarNombreApellido()const {
      Persona::mostrarNombreApellido();
  }
};

#endif  // SOCIO_H
