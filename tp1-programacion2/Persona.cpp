using namespace std;
#include <iostream>

class Persona {
 private:
  string nombre;
  string apellido;

 public:
  Persona(string nom, string ape) {
    nombre = nom;
    apellido = ape;
  }

  void mostrarNombreApellido() const {
    cout << "Nombre: " << nombre << ", Apellido: " << apellido << endl;
  }

  string getNombre() const { return nombre; }
  string getApellido() const { return apellido; }
  void setNombre(string nom) { nombre = nom; }
  void setApellido(string ape) { apellido = ape; }
};
