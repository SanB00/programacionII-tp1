using namespace std;

class Persona {
 private:
  string nombre;
  string apellido;

 public:
  Persona(string nom, string ape) : nombre(nom), apellido(ape) {}

  void mostrar() {
    cout << "Nombre: " << nombre << ", Apellido: " << apellido << endl;
  }

  string getNombre() { return nombre; }
  string getApellido() { return apellido; }
};
