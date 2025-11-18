#ifndef FECHA_H
#define FECHA_H

class Fecha {
 private:
  int dia, mes, anio;

 public:
  void cargarFechaManual();
  void mostrar() const;
  bool esUnaFechaValida() const;
  void cargarFechaDelDia();
};

#endif  // FECHA_H
