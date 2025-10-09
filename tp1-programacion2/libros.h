#ifndef LIBROS_H
#define LIBROS_H

class Libros {
private:
    int idLibro;
    char titulo[50];
    char autor[30];
    char editorial[30];
    bool eliminado;
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
};

#endif // LIBROS_H
