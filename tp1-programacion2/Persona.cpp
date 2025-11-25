#include <iostream>
#include <cstring> // Incluir esta cabecera para usar strncpy

using namespace std;

class Persona {
 protected:
  char nombre[30];
  char apellido[30];

 public:
  Persona(char* nom, char* ape) {
    strncpy(nombre, nom, sizeof(nombre) - 1);
    nombre[sizeof(nombre) - 1] = '\0';  // Asegurar terminación nula
    strncpy(apellido, ape, sizeof(apellido) - 1);
    apellido[sizeof(apellido) - 1] = '\0';  // Asegurar terminación nula
  }
  void mostrarNombreApellido() const {
    cout << "Nombre: " << nombre << ", Apellido: " << apellido << endl;
  }

  const char* getNombre() const { return nombre; }
  const char* getApellido() const { return apellido; }
  void setNombre(char* nom) { strncpy(nombre, nom, sizeof(nombre) - 1); }
  void setApellido(char* ape) { strncpy(apellido, ape, sizeof(apellido) - 1); }
};
