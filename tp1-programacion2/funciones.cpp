#include <iostream>
#include "libros.h"
#include "socio.h"
#include "prestamo.h"
using namespace std;

void mostrarMenuLibros()
{
    int opcionSeleccionada;

    /// quiero un menu hecho con un switch, q sino tire un error, no uses do while
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
}

void mostrarMenuSocios()
{
    int op;
    do
    {
        cout << "\n--- MENU SOCIOS ---\n";
        cout << "1. Alta\n2. Listar\n3. Baja Logica\n0. Volver\nOpcion: ";
        cin >> op;
        cin.ignore();
        if (op == 1)
        {
            Socio obj;
            obj.cargar();
            obj.guardar();
        }
        else if (op == 2)
        {
            Socio obj;
            int pos = 0;
            while (obj.leer(pos++))
            {
                obj.mostrar();
            }
        }
        else if (op == 3)
        {
            int id;
            cout << "Ingrese ID socio a eliminar: ";
            cin >> id;
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
        }
    } while (op != 0);
}

void menuPrestamos()
{
    int op;
    do
    {
        cout << "\n--- MENU PRESTAMOS ---\n";
        cout << "1. Alta\n2. Listar\n0. Volver\nOpcion: ";
        cin >> op;
        cin.ignore();
        if (op == 1)
        {
            Prestamo obj;
            obj.cargar();
            obj.guardar();
        }
        else if (op == 2)
        {
            Prestamo obj;
            int pos = 0;
            while (obj.leer(pos++))
            {
                obj.mostrar();
            }
        }
    } while (op != 0);
}
