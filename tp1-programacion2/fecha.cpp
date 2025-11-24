#include "Fecha.h"

#include <iostream>

#include "Utils.h"
#include "time.h"
using namespace std;
void Fecha::Fecha(int d, int m, int a) {
  dia = d;
  mes = m;
  anio = a;
}
void Fecha::cargarFechaDelDia() {
  time_t t = time(0);
  struct tm* now = localtime(&t);
  dia = now->tm_mday;
  mes = now->tm_mon + 1;
  anio = now->tm_year + 1900;
  mostrar();
}

void Fecha::cargarFechaManual() {
  cout << "Dia: ";
  cin >> dia;
  cout << "Mes: ";
  cin >> mes;
  cout << "Anio: ";
  cin >> anio;
  if (esUnaFechaValida()) {
    cout << "Fecha ingresada correctamente.\n";
  } else {
    cout << "Fecha invalida. Por favor, ingrese una fecha valida.\n";
    cargarFechaManual();
  }
}

void Fecha::mostrar() const { cout << dia << "/" << mes << "/" << anio; }

/*Corrobora si la fecha es válida*/
bool Fecha::esUnaFechaValida() const {
  if (anio < 1900 || anio > 2100) {
    cout << "Anio invalido. Por favor ingrese un anio entre el 1900 y 2100"
         << endl;
    return false;
  }
  if (mes < 1 || mes > 12) {
    cout << "Mes invalido. Por favor ingrese un mes entre 1 y 12." << endl;
    return false;
  }
  if (dia < 1 || dia > 31) {
    cout << "Dia invalido. Por favor ingrese un dia entre 1 y 31." << endl;
    return false;
  }

  int diasEnMes;
  switch (mes) {
    case 1:
    case 3:
    case 5:
    case 7:
    case 8:
    case 10:
    case 12:
      diasEnMes = 31;
      break;
    case 4:
    case 6:
    case 9:
    case 11:
      diasEnMes = 30;
      break;
    case 2:
      // Verificar si es año bisiesto
      if ((anio % 4 == 0 && anio % 100 != 0) || (anio % 400 == 0))
        diasEnMes = 29;
      else
        diasEnMes = 28;
      break;
    default:
      return false;  // Mes inválido
  }

  return dia <= diasEnMes;
}
