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
