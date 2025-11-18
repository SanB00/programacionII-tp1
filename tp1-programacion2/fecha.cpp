#include "Fecha.h"

#include <iostream>

#include "Utils.h"
using namespace std;

void Fecha::cargar() {
  cout << "Dia: ";
  dia = Utils::checkInputIsNumber();
  cout << "Mes: ";
  mes = Utils::checkInputIsNumber();
  cout << "Anio: ";
  anio = Utils::checkInputIsNumber();
  if (esUnaFechaValida()) {
    cout << "Fecha ingresada correctamente.\n";
  } else {
    cout << "Fecha invalida. Por favor, ingrese una fecha valida.\n";
    cargar();
  }
}

void Fecha::mostrar() const { cout << dia << "/" << mes << "/" << anio; }

/*Corrobora si la fecha es válida*/
bool Fecha::esUnaFechaValida() const {
  if (anio < 1900 || anio > 2100) return false;
  if (mes < 1 || mes > 12) return false;
  if (dia < 1 || dia > 31) return false;

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
