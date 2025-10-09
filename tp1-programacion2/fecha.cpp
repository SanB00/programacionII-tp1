#include <iostream>
#include "Fecha.h"
using namespace std;

void Fecha::cargar() {
    cout << "Dia: "; cin >> dia;
    cout << "Mes: "; cin >> mes;
    cout << "Anio: "; cin >> anio;
}

void Fecha::mostrar() const {
    cout << dia << "/" << mes << "/" << anio;
}
