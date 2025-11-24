#include <iostream>
#include <limits>

#include "Utils.h"
#include "Validaciones.cpp"
#include "libros.h"
#include "prestamo.h"
#include "socio.h"
using namespace std;

void menuLibros() {
  int opcionSeleccionada;
  do {
    cout << "\n--- MENU LIBROS ---\n";
    cout << "1. Alta de un Libro\n";
    cout << "2. Listar Libros\n";
    cout << "3. Baja Logica de un Libro\n";
    cout << "4. Buscar por ID\n";
    cout << "5  Buscar por Titulo\n";
    cout << "6. Buscar por Autor\n";
    cout << "7. Buscar por Editorial\n";
    cout << "0. Volver\n";
    cout << "Opcion: ";
    cin >> opcionSeleccionada;
    cin.ignore();

    switch (opcionSeleccionada) {
      default:
        cout << "Opcion invalida. Intente nuevamente.\n";
        break;
      case 1: {
        Libros obj;
        obj.cargar();
        obj.guardar();
        break;
      }

      case 2: {
        Libros obj;
        int pos = 0;
        while (obj.leer(pos++)) {
          obj.mostrar();
        }
        if (pos == 1) {
          cout << "No hay libros cargados.\n";
        }
        break;
      }
      case 3: {
        int id;
        cout << "Ingrese ID libro a eliminar: ";
        cin >> id;
        cin.ignore();
        Libros obj;
        int pos = 0;
        while (obj.leer(pos)) {
          if (obj.getIdLibro() == id && !obj.getEliminado()) {
            obj.setEliminado(true);
            obj.modificar(pos);
            cout << "Libro dado de baja.\n";
            break;
          }
          pos++;
        }
        break;
      }

      case 4: {
        int id;
        cout << "Ingrese ID del libro a buscar: ";
        Libros::buscarPorId(id);
        break;
      }
      case 5: {
        Libros::buscarPorTitulo();
        break;
      }
      case 6: {
        Libros::buscarPorAutor();
        break;
      }
      case 7: {
        Libros::buscarPorEditorial();
        break;
      }

      case 0:
        cout << "Volviendo al menu principal...\n";
        break;
    }

  } while (opcionSeleccionada != 0);
}

void menuSocios() {
  int opcionSeleccionada;
  do {
    cout << "\n--- MENU SOCIOS ---\n";
    cout << "1. Alta\n";
    cout << "2. Listar\n";
    cout << "3. Baja Logica\n";
    cout << "4. Buscar por ID\n";
    cout << "0. Volver\n";
    cout << "Opcion: ";
    cin >> opcionSeleccionada;
    cin.ignore();
    switch (opcionSeleccionada) {
      case 1: {
        Socio obj;
        obj.cargar();
        obj.guardar();
        break;
      }
      case 2: {
        Socio obj;
        int pos = 0;
        while (obj.leer(pos++)) {
          obj.mostrar();
        }
        if (pos == 1) {
          cout << "No hay socios cargados.\n";
        }
        break;
      }

      case 3: {
        int id;
        cout << "Ingrese ID socio a eliminar: ";
        cin >> id;
        cin.ignore();
        Socio obj;
        int pos = 0;
        while (obj.leer(pos)) {
          if (obj.getIdSocio() == id && !obj.getEliminado()) {
            obj.setEliminado(true);
            obj.modificar(pos);
            cout << "Socio dado de baja.\n";
            break;
          }
          pos++;
        }
        break;
      }

      case 4: {
        int id;
        cout << "Ingrese ID del socio a buscar: ";
        cin >> id;
        Socio obj;
        obj.buscar(id);
        break;
      }

      case 0:
        cout << "Volviendo al menu principal...\n";
        break;
      default:
        cout << "Opcion invalida. Intente nuevamente.\n";
        break;
    }

  } while (opcionSeleccionada != 0);
}

void menuPrestamos() {
  int opcionSeleccionada;
  bool comprobado = false;
  do {
    cout << "\n--- MENU PRESTAMOS ---\n";
    cout << "1. Alta\n";
    cout << "2. Listar\n";
    cout << "3. Buscar \n";
    cout << "0. Volver\n";
    cout << "Opcion: ";
    cin >> opcionSeleccionada;
    cin.ignore();
    switch (opcionSeleccionada) {
      case 1: {
        Prestamo obj;
        obj.cargar();
        obj.guardar();
        break;
      }

      case 2: {
        Prestamo obj;
        int pos = 0;
        while (obj.leer(pos++)) {
          obj.mostrar();
        }
        if (pos == 1) {
          cout << "No hay prestamos cargados.\n";
        }
        break;
      }

      case 3: {
        int id;
        Prestamo obj;
        cout << "ingrese id del prestamo" << endl;
        cin >> id;
        obj.buscarPorId(id);
        break;
      }

      case 0:
        cout << "Volviendo al menu...\n";
        break;

      default:
        cout << "Opcion invalida. Intente nuevamente.\n";
        break;
    }

  } while (opcionSeleccionada != false);
}
void menuInformes() {
  int opcionSeleccionada;
  do {
    cout << "\n--- MENU INFORMES ---\n";
    cout << "1. Socio con mas libros prestados\n";
    cout << "0. Volver\n";
    cout << "Opcion: ";
    cin >> opcionSeleccionada;
    cin.ignore();
    switch (opcionSeleccionada) {
      case 1: {
        Prestamo::buscarSocioConMasLibros();
        break;
      }
      case 0:
        cout << "Volviendo al menu principal...\n";
        break;
      default:
        cout << "Opcion invalida. Intente nuevamente.\n";
        break;
    }
  } while (opcionSeleccionada != 0);
}