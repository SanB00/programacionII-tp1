#ifndef FECHA_H
#define FECHA_H

class Fecha {
 private:
  int dia, mes, anio;

 public:
  Fecha(int d = 1, int m = 1, int a = 1900);
  void cargarFechaManual();
  void mostrar() const;
  bool esUnaFechaValida() const;
  void cargarFechaDelDia();
  int getMes() const { return mes; }
  int getAnio() const { return anio; }
  int getDia() const { return dia; }
};

#endif  // FECHA_H
