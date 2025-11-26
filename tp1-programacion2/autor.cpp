#include <string>

#include "Persona.cpp"

class Autor : public Persona {
 public:
  Autor(char* nombre, char* apellido) : Persona(nombre, apellido) {}
};
