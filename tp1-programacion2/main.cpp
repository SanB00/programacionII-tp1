#include <iostream>

#include "funciones.h"
using namespace std;

int main() {
  int opcion;
  do {
    cout << "\n===== MENU BIBLIOTECA =====\n";
    cout << "1. Gestionar Libros\n";
    cout << "2. Gestionar Socios\n";
    cout << "3. Gestionar Prestamos\n";
    cout << "0. Salir\n";
    cout << "Opcion: ";
    cin >> opcion;
    cin.ignore();
    switch (opcion) {
      case 1:
        menuLibros();
        break;
      case 2:
        menuSocios();
        break;
      case 3:
        menuPrestamos();
        break;
      default:
        cout << "Opcion invalida" << endl;
        break;
      case 0:
        cout << "Saliendo del programa..." << endl;
        break;
    }
  } while (opcion != 0);
  return 0;
}
