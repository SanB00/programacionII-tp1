#include <iostream>
#include <regex>
#include <string>

using namespace std;

/**
 Utiliza un patrón de expresión ^\\d+$ matches strings containing only digits.
 ^ Marca el inicio del string
 \\d relaciona los digitos numéricos (0-9).
 + para que valide más ocurrencias de digitos.
 $ Marca el fin del string.
 */
static bool tieneSoloNros(const string& str) {
  regex number_regex("^\\d+$");
  return regex_match(str, number_regex);
}

/**
 Verifica que la cadena esté cargada con al menos un valor. Se debe pasar un
 array char y su tamanio en nro Ejemplo char nombre[30]; cargarCadena(nombre,
 30);
 */
static bool cargarCadena(char* palabra, int tamanio) {
  int i = 0;
  fflush(stdin);
  for (i = 0; i < tamanio - 1; i++) {
    palabra[i] = cin.get();
    if (palabra[i] == '\n') {
      break;
    }
  }
  int largoDelTexto = strlen(palabra);
  if (largoDelTexto == 1 || largoDelTexto == 0) {
    cout << "Error: La cadena no puede estar vacia. Intente nuevamente: ";
    cargarCadena(palabra, tamanio);
    return false;
  }
  palabra[i] = '\0';
  fflush(stdin);
  return true;
}

static string verificarSistOperativo() {
  constexpr const char system_name[] =
#if defined(_WIN32)
      "Windows";
#elif defined(__APPLE__)
      "Apple";
#elif defined(__linux__)
      "Linux";
#else
#error "Unsupported operating system" // Error if none match
#endif
  // cout<< system_name;
  return system_name;
}

/**
 * Limpia la pantalla de la consola dependiendo del sistema operativo Windows o
 * Unix
 */
static void limpiarPantalla() {
  if (verificarSistOperativo() == "Apple") {
    cout << string(20, '\n');  // system("clear");
  } else if (verificarSistOperativo() == "Linux") {
    system("clear");
  } else if (verificarSistOperativo() == "Windows") {
    system("cls");
  }
}
