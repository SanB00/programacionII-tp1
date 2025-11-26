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
  bool esAnteriorA(Fecha fechaPosterior) const {
    if (anio < fechaPosterior.anio) {
      return true;
    } else if (anio == fechaPosterior.anio) {
      if (mes < fechaPosterior.mes) {
        return true;
      } else if (mes == fechaPosterior.mes) {
        if (dia < fechaPosterior.dia) {
          return true;
        }
      }
    }
    return false;
  };
  void cargarFechaDelDia();
  int getMes() const { return mes; }
  int getAnio() const { return anio; }
  int getDia() const { return dia; }
  static string mostrarMesEnLetras(int mes);
};

#endif  // FECHA_H
