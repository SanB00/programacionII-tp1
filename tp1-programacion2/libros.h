#ifndef LIBROS_H
#define LIBROS_H
#include"fecha.h"
class Libros {
private:
    int idLibro;
    char titulo[50];
    char autor[30];
    char editorial[30];
    bool eliminado;
    Fecha fechaalta;
public:
    void cargar();
    void mostrar() const;
    int getIdLibro() const;
    bool getEliminado() const;
    void setEliminado(bool e);

    /// Manejo de archivo
    bool guardar();
    bool leer(int pos);
    bool modificar(int pos);
    bool existeId(int id);
};

#endif // LIBROS_H
