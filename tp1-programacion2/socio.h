#ifndef SOCIO_H
#define SOCIO_H
#include "Persona.cpp"
#include "fecha.h"
class Socio : public Persona {
 private:
  int idSocio;
  char nombre[20];
  char apellido[20];
  char telefono[15];
  char direccion[50];
  char correo[40];
  Fecha fechaalta;
  bool eliminado;

 public:
  Socio() : Persona("", "") {
    idSocio = 0;
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
};

#endif  // SOCIO_H
