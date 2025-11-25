#ifndef SOCIO_H
#define SOCIO_H
#include "Persona.cpp"
#include "fecha.h"
class Socio : public Persona {
 private:
  int idSocio;
  static int siguienteId;  // Declaramos la variable estatica
  char telefono[10];
  char direccion[50];
  char correo[40];
  Fecha fechaAlta;
  bool eliminado;

 public:
  Socio() : Persona("", "") {
    idSocio = siguienteId;  // Asigna el ID actual
    Socio::siguienteId++;   // Incrementa para el proximo socio
    eliminado = false;
  }
  Socio(char* nom, char* ape, char* tel, char* dir, char* corr, Fecha fecha)
      : Persona(nom, ape) {
    idSocio = siguienteId;  // Asigna el ID actual
    Socio::siguienteId++;
    strncpy(telefono, tel, sizeof(telefono) - 1);
    telefono[sizeof(telefono) - 1] = '\0';
    strncpy(direccion, dir, sizeof(direccion) - 1);
    direccion[sizeof(direccion) - 1] = '\0';
    strncpy(correo, corr, sizeof(correo) - 1);
    correo[sizeof(correo) - 1] = '\0';
    fechaAlta = fecha;
    eliminado = false;
  }
  static int calcularMaximoId();
  int getIdSocio() const { return idSocio; }
  bool getEliminado() const { return eliminado; }
  void setEliminado(bool e) { eliminado = e; }

  void cargar();
  void mostrar() const;
  Socio buscar(int id);
  Fecha getFechaAlta() { return fechaAlta; }
  const char* getNombre() const { return nombre; }
  const char* getApellido() const { return apellido; }
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
