#ifndef PRESTAMO_H
#define PRESTAMO_H

#include "Fecha.h"

class Prestamo {
private:
    int idPrestamo;
    int idSocio;
    int idLibro;
    Fecha fechaPrestamo;
    Fecha fechaDevolucion;
public:
    void cargar();
    void mostrar() const;

    int getIdPrestamo() const;
    int getIdSocio() const;
    int getIdLibro() const;

    /// Manejo de archivo
    bool guardar();
    bool leer(int pos);
};

#endif // PRESTAMO_H
