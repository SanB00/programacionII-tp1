#ifndef PRESTAMO_H
#define PRESTAMO_H

#include "fecha.h"

class Prestamo {
 private:
  static int siguienteId;

  int idPrestamo;
  int idSocio;
  int idLibro;
  Fecha fechaPrestamo;
  Fecha fechaDevolucion;

 public:
  Prestamo() {
    idPrestamo = siguienteId;
    Prestamo::siguienteId++;
    //  eliminado = false;
  }
  static int calcularMaximoId();

  void cargar();
  void mostrar() const;

  int getIdPrestamo() const { return idPrestamo; };
  int getIdSocio() const { return idSocio; }
  int getIdLibro() const { return idLibro; }

  /// Manejo de archivo
  bool guardar();
  bool leer(int pos);
  static void buscarPorId(int id);
  static void buscarPorIdSocioYMostrar(int idSocio);
  static int cantidadPrestamosPorSocioArchivo(int idSocio);
  static void buscarSocioConMasLibros();
  static void buscarLibroMasPrestado();
  static int cantidadPrestamosPorMes(int mes, int anio);
  static void cantidadPrestamosPorAnio();
  static void cantidadPrestamosPorAnioYMes();
  static void cantidadPrestamosPorSocio();
};

#endif  // PRESTAMO_H
