#include <iostream>
#include <limits>

#include "Validaciones.cpp"
#include "fecha.h"
#include "libros.h"
#include "prestamo.h"
#include "socio.h"

using namespace std;

void menuLibros() {
  int opcionSeleccionada;
  do {
    system("cls");
    cout << "\n--- MENU LIBROS ---\n";
    cout << "1. Alta de un Libro\n";
    cout << "2. Listar Libros\n";
    cout << "3. Buscar por ID\n";
    cout << "4. Modificar\n";
    cout << "5. Activar\n";
    cout << "6. Desactivar (Baja Logica)\n";
    cout << "7  Buscar por Titulo\n";
    cout << "8. Buscar por Autor\n";
    cout << "9. Buscar por Editorial\n";
    cout << "0. Volver\n";
    cout << "Opcion: ";
    cin >> opcionSeleccionada;
    cin.ignore();
    system("cls");
    switch (opcionSeleccionada) {
      default:
        cout << "Opcion invalida. Intente nuevamente.\n";
        break;
      case 1: {
        Libros obj;
        obj.cargar();
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
        cout << "Ingrese ID libro a buscar: ";
        cin >> id;
        cin.ignore();
        Libros obj;
        obj.buscar(id);
        break;
      }
      case 4: {
        Libros obj;
        obj.modificarRegistro();
        break;
      }
      case 5: {
        Libros obj;
        obj.asignarEstadoDeRegistroComoActivo(true);
        break;
      }
      case 6: {
        Libros obj;
        obj.asignarEstadoDeRegistroComoActivo(false);
        break;
      }
      case 7: {
        Libros::buscarPorTitulo();
        break;
      }
      case 8: {
        Libros::buscarPorAutor();
        break;
      }
      case 9: {
        Libros::buscarPorEditorial();
        break;
      }

      case 0:
        cout << "Volviendo al menu principal...\n";
        return;
        break;
    }
    system("pause");
  } while (opcionSeleccionada != 0);
}

void menuSocios() {
  int opcionSeleccionada;
  do {
    system("cls");
    cout << "\n--- MENU SOCIOS ---\n";
    cout << "1. Alta\n";
    cout << "2. Listar\n";
    cout << "3. Buscar por ID\n";
    cout << "4. Modificar\n";
    cout << "5. Activar\n";
    cout << "6. Desactivar (Baja Logica)\n";
    cout << "0. Volver\n";
    cout << "Opcion: ";
    cin >> opcionSeleccionada;
    cin.ignore();
    system("cls");
    switch (opcionSeleccionada) {
      case 1: {
        Socio obj;
        obj.cargar();
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
        cout << "Ingrese ID del socio a buscar: ";
        cin >> id;
        Socio obj;
        obj.buscar(id);
        break;
      }
      case 4: {
        Socio obj;
        obj.modificarRegistro();
        break;
      }
      case 5: {
        Socio obj;
        obj.asignarEstadoDeRegistroComoActivo(true);
        break;
      }
      case 6: {
        Socio obj;
        obj.asignarEstadoDeRegistroComoActivo(false);
        break;
      }
      case 0:
        cout << "Volviendo al menu principal...\n";
        return;
        break;
      default:
        cout << "Opcion invalida. Intente nuevamente.\n";
        break;
    }
    system("pause");
  } while (opcionSeleccionada != 0);
}

void menuPrestamos() {
  int opcionSeleccionada;
  do {
    system("cls");
    cout << "\n--- MENU PRESTAMOS ---\n";
    cout << "1. Alta\n";
    cout << "2. Listar\n";
    cout << "3. Buscar \n";
    cout << "4. Eliminar prestamo (Baja Fisica) \n";
    cout << "0. Volver\n";
    cout << "Opcion: ";
    cin >> opcionSeleccionada;
    cin.ignore();
    system("cls");
    switch (opcionSeleccionada) {
      case 1: {
        Prestamo obj;
        obj.cargar();
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
      case 4: {
        Prestamo obj;
        obj.bajaFisica();
        break;
      }

      case 0:
        cout << "Volviendo al menu...\n";
        return;
        break;

      default:
        cout << "Opcion invalida. Intente nuevamente.\n";
        break;
    }
    system("pause");
  } while (opcionSeleccionada != false);
}
void menuInformes() {
  int opcionSeleccionada;
  do {
    system("cls");
    cout << "\n--- MENU INFORMES ---\n";
    cout << "1. Socio con mas libros prestados\n";
    cout << "2. Libro mas prestado\n";
    cout << "3. Cantidad de prestamos por anio\n";
    cout << "4. Cantidad de prestamos por mes\n";
    cout << "5. Cantidad de prestamos por Socio\n";
    cout << "0. Volver\n";
    cout << "Opcion: ";
    cin >> opcionSeleccionada;
    cin.ignore();
    system("cls");
    switch (opcionSeleccionada) {
      case 1: {
        Prestamo::buscarSocioConMasLibros();
        break;
      }
      case 2: {
        Prestamo::buscarLibroMasPrestado();
        break;
      }
      case 3: {
        Prestamo::cantidadPrestamosPorAnio();
        break;
      }
      case 4: {
        Prestamo::cantidadPrestamosPorAnioYMes();
        break;
      }
      case 5: {
        Prestamo::cantidadPrestamosPorSocio();
        break;
      }
      case 0:
        cout << "Volviendo al menu principal...\n";
        return;
        break;
      default:
        cout << "Opcion invalida. Intente nuevamente.\n";
        break;
    }
    system("pause");
  } while (opcionSeleccionada != 0);
}

void crearArchivoSiNoExiste(const char* nombreArchivo) {
  FILE* p = fopen(nombreArchivo, "ab");
  if (p != NULL) {
    fclose(p);
  }
}

void generarArchivosNecesariosConDatosFicticios() {
  crearArchivoSiNoExiste("libros.dat");
  crearArchivoSiNoExiste("socios.dat");
  Fecha fechaAlta = Fecha(1, 9, 2025);
  Socio obj =
      Socio(const_cast<char*>("Juan"), const_cast<char*>("Perez"),
            const_cast<char*>("11111111"), const_cast<char*>("Calle Falsa 123"),
            const_cast<char*>("aaaa@mail.com"), fechaAlta);
  obj.guardar();
  Socio obj2 =
      Socio(const_cast<char*>("Lucila"), const_cast<char*>("G"),
            const_cast<char*>("2222222"), const_cast<char*>("Calle Hola 123"),
            const_cast<char*>("hola@gmail.com"), fechaAlta);
  obj2.guardar();
  Socio obj3 = Socio(const_cast<char*>("Tomas"), const_cast<char*>("Mazza"),
                     const_cast<char*>("3333333"),
                     const_cast<char*>("Calle Estudio 2043"),
                     const_cast<char*>("estudio@gmail.com"), fechaAlta);
  obj3.guardar();
  crearArchivoSiNoExiste("prestamos.dat");
}
