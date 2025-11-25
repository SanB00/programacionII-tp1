#include <iostream>

#include "funciones.h"
#include "Validaciones.cpp"
using namespace std;

int main() {
  generarArchivosNecesariosConDatosFicticios();
  int opcionSeleccionada;
  do {
    limpiarPantalla();
    cout << "\n===== MENU BIBLIOTECA =====\n";
    cout << "1. Gestionar Libros\n";
    cout << "2. Gestionar Socios\n";
    cout << "3. Gestionar Prestamos\n";
    cout << "4. Informes\n";
    cout << "0. Salir\n";
    cout << "Opcion: ";
    cin >> opcionSeleccionada;
    cin.ignore();
    switch (opcionSeleccionada) {
      case 1:
        menuLibros();
        break;
      case 2:
        menuSocios();
        break;
      case 3:
        menuPrestamos();
        break;
      case 4:
        menuInformes();
        break;
      default:
        cout << "Opcion invalida" << endl;
        break;
      case 0:
        cout << "Saliendo del programa..." << endl;
        break;
    }
  } while (opcionSeleccionada != 0);
  return 0;
}
