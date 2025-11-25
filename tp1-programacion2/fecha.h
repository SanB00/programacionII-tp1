#ifndef FECHA_H
#define FECHA_H
#include <string>
using namespace std;
class Fecha {
 private:
  int dia, mes, anio;

 public:
  Fecha(int d = 1, int m = 1, int a = 1900);
  void cargarFechaManual();
  void mostrar() const;
  string toString() const {
    return to_string(dia) + "/" + to_string(mes) + "/" + to_string(anio);
  }
  bool esUnaFechaValida() const;
  void cargarFechaDelDia();
  int getMes() const { return mes; }
  int getAnio() const { return anio; }
  int getDia() const { return dia; }
  static string mostrarMesEnLetras(int mes);
};

#endif  // FECHA_H
