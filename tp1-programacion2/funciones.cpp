#include <iostream>
#include "libros.h"
#include "socio.h"
#include "prestamo.h"
using namespace std;
void mostrarMenuLibros()
{
    int opcionSeleccionada;
    do
    {
        cout << "\n--- MENU LIBROS ---\n";
        cout << "1. Alta\n2. Listar\n3. Modificar\n4. Baja Logica\n0. Volver\nOpcion: ";
        cin >> opcionSeleccionada;
        cin.ignore();
        switch (opcionSeleccionada)
        {
        case 1:
        {
            Libros obj;
            obj.cargar();
            obj.guardar();
            break;
        }
        case 2:
        {
            Libros obj;
            int pos = 0;
            while (obj.leer(pos++))
            {
                obj.mostrar();
            }
            break;
        }
        case 3:
        {
            int id;
            cout << "Ingrese ID libro a modificar: ";
            cin >> id;
            cin.ignore();
            Libros obj;
            int pos = 0;
            while (obj.leer(pos))
            {
                if (obj.getIdLibro() == id && !obj.getEliminado())
                {
                    obj.cargar();
                    obj.modificar(pos);
                    cout << "Libro modificado.\n";
                    break;
                }
                pos++;
            }
            break;
        }
        case 4:
        {
            int id;
            cout << "Ingrese ID libro a eliminar: ";
            cin >> id;
            cin.ignore();
            Libros obj;
            int pos = 0;
            while (obj.leer(pos))
            {
                if (obj.getIdLibro() == id && !obj.getEliminado())
                {
                    obj.setEliminado(true);
                    obj.modificar(pos);
                    cout << "Libro dado de baja.\n";
                    break;
                }
                pos++;
            }
            break;
        }
        case 0:
            // Volver al menu principal
            break;
        default:
            cout << "Opcion invalida. Intente nuevamente.\n";
        }
    } while (opcionSeleccionada != 0);
}

void mostrarMenuSocios()
{
    int opcion;
    do
    {
        cout << "\n--- MENU SOCIOS ---\n";
        cout << "1. Alta\n2. Listar\n3. Modificar\n4. Baja Logica\n0. Volver\nOpcion: ";
        cin >> opcion;
        cin.ignore();
        switch (opcion)
        {
        case 1:
        {
            Socio obj;
            obj.cargar();
            obj.guardar();
            break;
        }
        case 2:
        {
            Socio obj;
            int pos = 0;
            while (obj.leer(pos++))
            {
                obj.mostrar();
            }
            break;
        }
        case 3:
        {
            int id;
            cout << "Ingrese ID socio a modificar: ";
            cin >> id;
            cin.ignore();
            Socio obj;
            int pos = 0;
            while (obj.leer(pos))
            {
                if (obj.getIdSocio() == id && !obj.getEliminado())
                {
                    obj.cargar();
                    obj.modificar(pos);
                    cout << "Socio modificado.\n";
                    break;
                }
                pos++;
            }
            break;
        }
        case 4:
        {
            int id;
            cout << "Ingrese ID socio a eliminar: ";
            cin >> id;
            cin.ignore();
            Socio obj;
            int pos = 0;
            while (obj.leer(pos))
            {
                if (obj.getIdSocio() == id && !obj.getEliminado())
                {
                    obj.setEliminado(true);
                    obj.modificar(pos);
                    cout << "Socio dado de baja.\n";
                    break;
                }
                pos++;
            }
            break;
        }
        case 0:
            // Volver al menu principal
            break;
        default:
            cout << "Opcion invalida. Intente nuevamente.\n";
        }
    } while (opcion != 0);
}

void mostrarMenuPrestamos()
{
    int opcion;

    do
    {
        cout << "\n--- MENU PRESTAMOS ---\n";
        cout << "1. Alta\n2. Listar\n0. Volver\nOpcion: ";
        cin >> opcion;
        cin.ignore();

        switch (opcion)
        {
        case 1:
        {
            Prestamo obj;
            obj.cargar();
            obj.guardar();
            break;
        }

        case 2:
        {
            Prestamo obj;
            int pos = 0;
            while (obj.leer(pos++))
            {
                obj.mostrar();
            }
            break;
        }
        case 0:
            // Volver al menu principal
            break;
        default:
            cout << "Opcion invalida. Intente nuevamente.\n";
        }
    } while (opcion != 0);
}
