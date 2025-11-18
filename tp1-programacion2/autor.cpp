#include <string>

#include "Persona.cpp"

class Autor : public Persona {
 public:
  Autor(string nombre, string apellido) : Persona(nombre, apellido) {}
};