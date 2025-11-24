#ifndef PRESTAMO_H
#define PRESTAMO_H

#include "fecha.h"

class Prestamo {
 private:
  int idPrestamo;
  int idSocio;
  int idLibro;
  Fecha fechaPrestamo;
  Fecha fechaDevolucion;

 public:
  void cargar();
  void mostrar() const;

  int getIdPrestamo() const;
  int getIdSocio() const;
  int getIdLibro() const;

  /// Manejo de archivo
  bool guardar();
  bool leer(int pos);
  static void buscarPorId(int id);
  static void buscarSocioConMasLibros();
  static void buscarLibroMasPrestado();
  static int cantidadPrestamosPorMes(int mes, int anio);
  static void cantidadPrestamosPorAnio();
};

#endif  // PRESTAMO_H
